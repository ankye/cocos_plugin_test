declare class IPluginDelegate {
    constructor()
    onPluginOpen(...data)
    onPluginClose(...data)
    onPluginData(...data)
    onPluginDataWithBuffer(...data)
}
declare class COCOS_CC_PLUGIN_TP__ {
    constructor(delegate: IPluginDelegate)
    attrInt: number
    version(): string
    openPlugin(logLv: number): void
    closePlugin(): void
    getBuffer(val_ptr: number, size: number): Uint8Array;
    sendData(data: Uint8Array, size: number): void;
    generateImageData(width: number, height: number): Uint8Array;
}
