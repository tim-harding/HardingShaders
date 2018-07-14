import pymel.core as pm
import maya.cmds as cmds
from mtoa.ui.ae.shaderTemplate import ShaderAETemplate
 
class AEaiCameraTextureTemplate(ShaderAETemplate):

    def setup(self):
        self.addSwatch()
        self.beginScrollLayout()
        self.addCustom('message', 'AEshaderTypeNew', 'AEshaderTypeReplace')

        self.addCustom('camera_name', self.camera_select_new, self.camera_select_replace)

        self.endLayout()
        pm.mel.AEdependNodeTemplate(self.nodeName)
        self.addExtraControls()
        self.endScrollLayout()


    def camera_select_new(self, node_name):
        self.camera_menu = cmds.optionMenu(
            label="Camera", 
            changeCommand=self.camera_select_change, 
            beforeShowPopup=self.refresh_menu,
            visibleChangeCommand=self.refresh_menu
        )

        # Get the camera name attribute, or create it with a default if nonexistant
        try:
            camera = cmds.getAttr(self.nodeAttr('camera_name'))
        except Exception:
            camera = self.get_filtered_cameras()[0]
            cmds.addAttr(dataType='string', longName='camera_name')
            cmds.setAttr(self.nodeAttr('camera_name'), camera, type='string')           

        self.update_shader_parameters()

       
    def camera_select_replace(self, node_name):
        pass


    def camera_select_change(self, selection):
        cmds.setAttr(self.nodeAttr('camera_name'), selection, type='string')
        self.update_shader_parameters()


    def refresh_menu(self, *args):
        # Clear out old items
        items = cmds.optionMenu(self.camera_menu, q=True, itemListLong=True)
        if items != None:
            for item in items:
                cmds.deleteUI(item, menuItem=True)

        # Get the cameras in our scene
        cameras = self.get_filtered_cameras()

        # Create menu items
        cmds.setParent(self.camera_menu, menu=True)
        for camera in cameras:
            cmds.menuItem(label=camera)

        # Set which camera is currently selected, if any
        current_camera = cmds.getAttr(self.nodeAttr('camera_name'))
        for i, camera in enumerate(cameras):
            if camera == current_camera:
                # select is 1-indexed
                cmds.optionMenu(self.camera_menu, e=True, select=i + 1)


    def update_shader_parameters(self):
        camera_name = cmds.getAttr(self.nodeAttr('camera_name'))
        cmds.connectAttr(
            '{}.focalLength'.format(camera_name), 
            self.nodeAttr('camera_focalLength'), 
            force=True
        )
        
        cmds.connectAttr(
            '{}.horizontalFilmAperture'.format(camera_name), 
            self.nodeAttr('camera_apertureHorizontal'), 
            force=True
        )

        cmds.connectAttr(
            '{}.verticalFilmAperture'.format(camera_name), 
            self.nodeAttr('camera_apertureVertical'), 
            force=True
        )

        cmds.connectAttr(
            '{}.parentMatrix'.format(camera_name), 
            self.nodeAttr('camera_matrix'), 
            force=True
        )


    def get_filtered_cameras(self):
        cameras = []
        for camera in cmds.ls(cameras=True):
            isCameraOrthographic = cmds.camera(camera, q=True, orthographic=True)
            # Exclude default ortho cameras
            if not isCameraOrthographic:
                cameras.append(camera)

        return cameras
