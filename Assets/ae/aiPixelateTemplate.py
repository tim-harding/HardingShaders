import pymel.core as pm
import maya.cmds as cmds
from mtoa.ui.ae.shaderTemplate import ShaderAETemplate
 
class AEaiPixelateTemplate(ShaderAETemplate):

    def setup(self):
        self.addSwatch()
        self.beginScrollLayout()
        self.addCustom('message', 'AEshaderTypeNew', 'AEshaderTypeReplace')

        self.addControl("input", label="Input")
        self.addControl("resolution", label="Resolution")

        self.endLayout()
        pm.mel.AEdependNodeTemplate(self.nodeName)
        self.addExtraControls()
        self.endScrollLayout()