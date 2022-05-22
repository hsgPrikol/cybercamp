#include "cameraasist.h"

CameraAsist::CameraAsist(QObject *parent) : QObject(parent)
{

}

QString CameraAsist::recognizeQR(QString path)
{
    QImage imageToDecode("C:\\img.jpg");
    QZXing decoder;
    decoder.setDecoder( QZXing::DecoderFormat_QR_CODE );

    decoder.setSourceFilterType(QZXing::SourceFilter_ImageNormal | QZXing::SourceFilter_ImageInverted);
    decoder.setTryHarderBehaviour(QZXing::TryHarderBehaviour_ThoroughScanning | QZXing::TryHarderBehaviour_Rotate);

    QString result =  decoder.decodeImage(imageToDecode);

    return result;
}
