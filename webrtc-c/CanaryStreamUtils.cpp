/**
 * Kinesis Video Producer Continuous Retry Stream Callbacks
 */
#define LOG_CLASS "CanaryStreamCallbacks"
#include "CanaryStreamUtils.h"

STATUS setUpCloudwatch(Aws::CloudWatch::CloudWatchClient* cwClient,
                       PSampleConfiguration pSampleConfiguration,
                       PCanaryCloudwatchObject* ppCanaryCloudwatchObject)
{
    ENTERS();
    STATUS retStatus = STATUS_SUCCESS;
    Aws::CloudWatch::Model::Dimension dimension;
    PCanaryCloudwatchObject pCanaryCloudwatchObject = NULL;

    CHK(ppCanaryCloudwatchObject != NULL && pSampleConfiguration != NULL, STATUS_NULL_ARG);

    // Allocate the entire structure
    pCanaryCloudwatchObject = (PCanaryCloudwatchObject) MEMCALLOC(1, SIZEOF(CanaryCloudwatchObject));
    CHK(pCanaryCloudwatchObject != NULL, STATUS_NOT_ENOUGH_MEMORY);

    pCanaryCloudwatchObject->pCwClient = cwClient;

    dimension.SetName(pSampleConfiguration->);
    dimension.SetValue("WebRTCSDK");

    pCanaryCloudwatchObject->packetsSentPercentage.SetMetricName("PacketsSentPercentage");
    pCanaryCloudwatchObject->persistedAckDatum.SetMetricName("PersistedAckLatency");
    pCanaryCloudwatchObject->bufferingAckDatum.SetMetricName("BufferedAckLatency");
    pCanaryCloudwatchObject->streamErrorDatum.SetMetricName("StreamError");
    pCanaryCloudwatchObject->currentFrameRateDatum.SetMetricName("FrameRate");
    pCanaryCloudwatchObject->contentStoreAvailableSizeDatum.SetMetricName("StorageSizeAvailable");
    pCanaryCloudwatchObject->currentViewDurationDatum.SetMetricName("CurrentViewDuration");
    pCanaryCloudwatchObject->memoryAllocationSizeDatum.SetMetricName("MemoryAllocation");

    pCanaryCloudwatchObject->packetsSentPercentage.AddDimensions(dimension);
    pCanaryCloudwatchObject->persistedAckDatum.AddDimensions(dimension);
    pCanaryCloudwatchObject->bufferingAckDatum.AddDimensions(dimension);
    pCanaryCloudwatchObject->streamErrorDatum.AddDimensions(dimension);
    pCanaryCloudwatchObject->currentFrameRateDatum.AddDimensions(dimension);
    pCanaryCloudwatchObject->contentStoreAvailableSizeDatum.AddDimensions(dimension);
    pCanaryCloudwatchObject->currentViewDurationDatum.AddDimensions(dimension);
    pCanaryCloudwatchObject->memoryAllocationSizeDatum.AddDimensions(dimension);

CleanUp:

    if (STATUS_FAILED(retStatus)) {
        pCanaryCloudwatchObject = NULL;
        MEMFREE(pCanaryCloudwatchObject);
    }

    if(ppCanaryCloudwatchObject != NULL) {
        *ppCanaryCloudwatchObject = (PCanaryCloudwatchObject) pCanaryCloudwatchObject;
    }

    LEAVES();
    return retStatus;
}
