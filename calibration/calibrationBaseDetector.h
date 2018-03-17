
#pragma once

#include "calibrationCommon.h"
#include "calibrationPatternUtils.h"

#include <panels/SPatternDetectorPanel.h>
#include <pthread.h>

using namespace std;

namespace calibration
{


    class BaseDetector
    {

        protected :



        enum
        {
            // For detection part
            STEP_BASE = 0,
            STEP_MASK = 1,
            STEP_EDGES = 2,
            STEP_BLOBS = 3,
            STEP_TRACKING = 4,

            // For refining part
            STEP_REFINING_UNDISTORTED = 5,
            STEP_REFINING_FRONTO = 6,
            STEP_REFINING_MASK = 7,
            STEP_REFINING_EDGES = 8,
            STEP_REFINING_FEATURES = 9,
            STEP_REFINING_PROJECTED = 10,
            STEP_REFINING_DISTORTED = 11,

            MAX_STAGES = 12
        };

        calibcv::SPatternDetectorPanel* m_pipelinePanel;
 
        cv::Size m_size;
        int m_numPoints;

        vector< cv::Point2f > m_patternPoints;
        vector< cv::Point2f > m_patternPointsRefined;

        vector< vector< cv::Point2f > > m_batchPointsRefined;
        vector< cv::Mat > m_batchImagesRefinationResult;

        vector< vector< cv::Point2f > > m_workingDataBatchPoints;
        vector< cv::Mat > m_workingDataBatchImages;
        cv::Mat m_workingDataCameraMatrix;
        cv::Mat m_workingDataDistortionCoefficients;

        cv::Mat m_frame;
        cv::Size m_frameSize;

        bool m_hasRefinedPoints;
        bool m_isRefining;
        
        pthread_t m_threadHandle;

        vector< cv::Mat > m_stepImageResults;

        void _refineBatchInternal( const vector< cv::Mat >& batchImagesToRefine,
                                   const vector< vector< cv::Point2f > >& batchPointsToRefine,
                                   const cv::Mat& cameraMatrix,
                                   const cv::Mat& distortionCoefficients );

        void _refineSingleInternal( const cv::Mat& imageToRefine,
                                    const vector< cv::Point2f >& pointsToRefine,
                                    const cv::Mat& cameraMatrix,
                                    const cv::Mat& distortionCoefficients );

        void _refiningConversionDirect( const cv::Mat& image2refine, 
                                        cv::Mat& frontoView, cv::Mat& frontoTransform,
                                        const vector< cv::Point2f >& patternPoints,
                                        const cv::Mat& cameraMatrix,
                                        const cv::Mat& distortionCoefficients,
                                        bool showIntermediateResults = false );

        bool _refiningDetection( const cv::Mat& input, vector< cv::Point2f >& frontoRefinedPoints,
                                 bool showIntermediateResults = false );

        virtual bool _refiningDetectionInternal( const cv::Mat& input, vector< cv::Point2f >& frontoRefinedPoints,
                                                 bool showIntermediateResults = false );

        void _refiningConversionInverse( const vector< cv::Point2f>& frontoRefinedPoints,
                                         vector< cv::Point2f >& refinedPoints,
                                         cv::Mat& refinedImageResult,
                                         const cv::Mat& inverseFrontoTransform,
                                         const cv::Mat& originalView,
                                         const vector< cv::Point2f >& originalPoints,
                                         const cv::Mat& cameraMatrix,
                                         const cv::Mat& distortionCoefficients,
                                         bool showIntermediateResults = false );

        BaseDetector( const cv::Size& size );

        public :

        ~BaseDetector();

        void update();

        virtual bool run( const cv::Mat& input, const DetectionInfo& detInfo ) = 0;
        virtual void getDetectedPoints( vector< cv::Point2f >& iPoints ) = 0;

        // Shared steps for fronto parallel transformation
        void refineBatch( const vector< cv::Mat >& batchImagesToRefine,
                          const vector< vector< cv::Point2f > >& batchPointsToRefine,
                          const cv::Mat& cameraMatrix,
                          const cv::Mat& distortionCoefficients,
                          bool useThreads = true,
                          bool showIntermediateResults = false );

        // void detectBatch( const vector< cv::Mat >& batchImagesToDetect,
        //                   bool useThreads = true );

        bool isRefining() { return m_isRefining; }

        bool hasRefinationToPick() { return m_hasRefinedPoints; }
        
        void grabRefinationBatch( vector< cv::Mat >& batchRefinedImages,
                                  vector< vector< cv::Point2f > >& batchRefinedPoints );

        static void* refinerWorker( void* pDetector );

    };


}