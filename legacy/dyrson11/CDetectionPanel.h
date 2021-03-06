
#pragma once

#include "CCommon.h"

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

#define BLUR_SIZE 3
#define CANNY_MIN 50
#define CANNY_MAX 150
#define CANNY_SOBEL_MASK_SIZE 3
#define ELLIPSE_COUNT_THRESHOLD 5

namespace calibcv { namespace detection {

    enum _windowID
    {
        MASK = 0,
        MASKED = 1,
        EDGES = 2,
        CONTOURS = 3,
        ELLIPSES = 4
    };

    static unordered_map< _windowID, string > WINDOW_MAP( { { MASK, "cf - mask" },
                                                            { MASKED, "cf - masked" },
                                                            { EDGES, "cf - edges" },
                                                            { CONTOURS, "cf - contours" },
                                                            { ELLIPSES, "cf - ellipses" } } );

    class CDetectionPanel
    {

        private :

        int m_blurSize;
        int m_cannyMin;
        int m_cannyMax;
        int m_cannySobelMaskSize;
        int m_cannySobelMaskDelta;
        int m_ellipseCountThreshold;

        CDetectionPanel();
        void init();

        public :

        static CDetectionPanel* INSTANCE;
        static CDetectionPanel* create();
        static void release();

        ~CDetectionPanel();

        void showMask( const cv::Mat& mat );
        void showMasked( const cv::Mat& mat );
        void showEdges( const cv::Mat& mat );
        void showContours( const cv::Mat& mat );
        void showEllipses( const cv::Mat& mat );

        int blurSize() { return m_blurSize; }
        int cannyMin() { return m_cannyMin; }
        int cannyMax() { return m_cannyMax; }
        int cannySobelMaskSize() { return m_cannySobelMaskSize; }
        int ellipseCountThreshold() { return m_ellipseCountThreshold; }

        static void onTrackbarCallback( int dummyInt, void* dummyPtr );

    };





}}