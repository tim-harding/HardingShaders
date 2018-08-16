import pymel.core as pm
import mtoa.utils as utils
from mtoa.ui.ae.shaderTemplate import ShaderAETemplate
 
class AEaiStencilGetTemplate(ShaderAETemplate):
 
    def setup(self):
        self.addSwatch()
        self.beginScrollLayout()
        self.addCustom('message', 'AEshaderTypeNew', 'AEshaderTypeReplace')

        self.addControl("stencil", label="Stencil")

        self.endLayout()
        pm.mel.AEdependNodeTemplate(self.nodeName)
        self.addExtraControls()
        self.endScrollLayout()