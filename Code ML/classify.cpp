#include <jetson-inference/imageNet.h>
#include <jetson-utils/loadImage.h>

int main(int argc, char** argv){
    if(argc < 2){
        printf("aaaaa");
        return 0;
    }

    const char* imgFilename = argv[1];

    uchar3* imgPtr = NULL;
    int imgWidth = 0;
    int imgHeight = 0;

    if(!loadImage(imgFilename, &imgPtr, &imgWidth, &imgHeight)){
        printf("fail!!!");
        return 0;
    }

    imageNet* net = imageNet::Create("googlenet");

    if(!net){
        printf("gagal imageNet");
        return 0;
    }

    float confidence = 0.0;

    const int classIndex = net->Classify(imgPtr, imgWidth, imgHeight, &confidence);

    if(classIndex >= 0){
        const char* classDesc = net->GetClassDesc(classIndex);
        printf("Terdeteksi '%s' (class #%i) dengan confidence %f%%\n", classDesc, classIndex, confidence * 100.0f);

    } else{
        printf("gagal klasifikasi");

    }

    delete net;
    return 0;
}