import { __private, _decorator,SpriteFrame, Component, gfx, Node, RichText, Sprite, Texture2D, sys } from 'cc'

const { ccclass, property } = _decorator

//@ts-ignore
let WASM = window.COCOS_CC_PLUGIN_TP__;
        
@ccclass('PluginTest')
export class PluginTest extends Component {
    @property({ type: RichText })
    richText: RichText = null
    @property({ type: Sprite })
    sprite: Sprite = null

    width = 500
    height = 500
    texData;
    plugin;
    start() {
        
    }
    onClick() {
        //@ts-ignore
        let plugin = sys.isNative? new COCOS_CC_PLUGIN_TP__(this): new WASM.COCOS_CC_PLUGIN_TP__(this)
        this.plugin = plugin; 
        plugin.attrInt = 1;
        console.log("attrInt", plugin.attrInt);
        plugin.openPlugin(1)
        console.log(plugin.version());
        this.richText.string = plugin.version();
        this.texData = new Uint8Array(this.width * this.height * 4)
        for (let i = 0; i < this.texData.length; i++) { 
            this.texData[i] = i % 255;
        }
        plugin.sendData(this.texData, this.texData.length);
        plugin.closePlugin()
        
    }
    update(deltaTime: number) { }
    resetSpriteFrame() { 
        let texture = new Texture2D();
        texture.setFilters(Texture2D.Filter.LINEAR, Texture2D.Filter.LINEAR);
        texture.setMipFilter(Texture2D.Filter.LINEAR);
        texture.setWrapMode(Texture2D.WrapMode.CLAMP_TO_EDGE, Texture2D.WrapMode.CLAMP_TO_EDGE);

        texture.reset({
            width: this.width,
            height: this.height,
            //@ts-ignore
            format: gfx.Format.RGBA8
        });    
        texture.uploadData(this.texData);
        let spf = new SpriteFrame();
        spf.texture = texture;
        this.sprite.spriteFrame = spf;
    }
    onPluginOpen( ...data) {
        console.log('onPluginOpen', data)
    }
    onPluginClose(...data) {
        console.log('onPluginClose', data)
    }
    onPluginDataWithBuffer(...data)
    {
        console.log('onPluginDataWithBuffer', data)        
    }
    onPluginData( ...data) {
        console.log('onPluginData', data)
        let p = data[0];
        let size = data[1];
        let outArray = this.plugin.getBuffer(p, size);
        this.texData = outArray;
        
        

        this.resetSpriteFrame();
        console.log(this.texData);
    }

    
}
