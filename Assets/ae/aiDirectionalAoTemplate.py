import pymel.core as pm
import mtoa.utils as utils
from mtoa.ui.ae.shaderTemplate import ShaderAETemplate
 
class AEaiDirectionalAoTemplate(ShaderAETemplate):
 
    def setup(self):
        self.addSwatch()
        self.beginScrollLayout()
        self.addCustom('message', 'AEshaderTypeNew', 'AEshaderTypeReplace')

        self.addControl("direction", label="Direction")
        self.addControl("falloff", label="Falloff")
        self.addControl("spread", label="Spread")
        self.addControl("samples", label="Samples")
        self.addControl("self", label="Self only")
        self.addControl("reflect", label="Reflective AO")

        self.endLayout()
        pm.mel.AEdependNodeTemplate(self.nodeName)
        self.addExtraControls()
        self.endScrollLayout()