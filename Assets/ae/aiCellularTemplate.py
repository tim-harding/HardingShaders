import pymel.core as pm
import mtoa.utils as utils
from mtoa.ui.ae.shaderTemplate import ShaderAETemplate
 
class AEaiCellularTemplate(ShaderAETemplate):
 
    def setup(self):
        self.addSwatch()
        self.beginScrollLayout()
        self.addCustom('message', 'AEshaderTypeNew', 'AEshaderTypeReplace')

        self.addControl("octaves", label="Octaves")
        self.addControl("feature", label="feature")
        self.addControl("space", label="Space")
        self.addControl("scale", label="Scale")
        self.addControl("offset", label="Offset")
        self.addControl("position", label="Position")

        self.endLayout()
        pm.mel.AEdependNodeTemplate(self.nodeName)
        self.addExtraControls()
        self.endScrollLayout()