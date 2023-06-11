#ifndef TGASICEEGDATA_H
#define TGASICEEGDATA_H
#ifdef __cplusplus
extern "C" {
#endif
typedef struct _TG_AsicEegData {
    unsigned int eegDelta; // 100000 / 1500000 . 0.5-2.75hz
    unsigned int eegTheta; // 300000 / 600000 . 3.5-6.75hz
    unsigned int eegLowAlpha; // 2500 / 75000 . 7.5-9.25hz
    unsigned int eegHighAlpha; // 2500 / 150000 . 10-11.75hz
    unsigned int eegLowBeta; // 1500 / 60000 . 13-16.75hz
    unsigned int eegHighBeta; // 2500 / 60000 . 18-29.75hz
    unsigned int eegLowGamma; // 5000 / 300000 . 31-39.75hz
    unsigned int eegMidGamma; // 5000 / 300000 . 41-49.75hz
} TG_AsicEegData;

#ifdef __cplusplus
}
#endif

#endif // TGASICEEGDATA_H
