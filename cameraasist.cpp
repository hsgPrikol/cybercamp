#include "cameraasist.h"

CameraAsist::CameraAsist(QObject *parent) : QObject(parent)
{

}

QString CameraAsist::recognizeQR(QString path)
{
    QImage imageToDecode(path);
    QZXing decoder;
    decoder.setDecoder( decoder.DecoderFormat_QR_CODE );

    decoder.setSourceFilterType(QZXing::SourceFilter_ImageNormal);
    decoder.setTryHarderBehaviour(QZXing::TryHarderBehaviour_ThoroughScanning | QZXing::TryHarderBehaviour_Rotate);

    return decoder.decodeImage(imageToDecode);
}
