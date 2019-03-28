import pymel.core as pm
import maya.cmds as cmds
from mtoa.ui.ae.shaderTemplate import ShaderAETemplate
import mtoa.aovs as ma


class AEaiWriteFloatAdditiveTemplate(ShaderAETemplate):
    def setup(self):
        self.addSwatch()
        self.beginScrollLayout()
        self.addCustom('message', 'AEshaderTypeNew', 'AEshaderTypeReplace')

        self.addControl('beauty', label='Beauty')
        self.addControl('input', label='Input')
        self.addCustom('aov_name', self.aov_select_new, self.aov_select_replace)

        self.endLayout()
        pm.mel.AEdependNodeTemplate(self.nodeName)
        self.addExtraControls()
        self.endScrollLayout()

    def aov_select_new(self, node_name):
        self.camera_menu = cmds.optionMenu(
            label="AOV",
            changeCommand=self.aov_select_change,
            beforeShowPopup=self.refresh_menu,
            visibleChangeCommand=self.refresh_menu
        )

        self.refresh_menu()

    def aov_select_replace(self, node_name):
        pass

    def aov_select_change(self, selection):
        cmds.setAttr(self.nodeAttr('aov_name'), selection, type='string')

    def refresh_menu(self, *args):
        # Clear out old items
        items = cmds.optionMenu(self.camera_menu, q=True, itemListLong=True)
        if items is not None:
            for item in items:
                cmds.deleteUI(item, menuItem=True)

        aovs = self.get_aovs()

        # Create menu items
        cmds.setParent(self.camera_menu, menu=True)
        cmds.menuItem(label='<None>')
        for aov in aovs:
            cmds.menuItem(label=aov)

        # Set which camera is currently selected, if any
        current_aov = cmds.getAttr(self.nodeAttr('aov_name'))
        for i, aov in enumerate(aovs):
            if aov == current_aov:
                # select is 1-indexed
                cmds.optionMenu(self.camera_menu, e=True, select=i + 2)

    def get_aovs(self):
        interface = ma.AOVInterface()
        aov_nodes = interface.getAOVNodes(names=True)  # (aovName, aovNode)
        names = [node[0] for node in aov_nodes]
        return names
