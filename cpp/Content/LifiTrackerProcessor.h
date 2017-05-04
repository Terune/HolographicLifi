//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#pragma once

namespace HolographicLifiTracker
{
    class VideoFrameProcessor;

    // Class to manage the FaceAnalysis::FaceTracker object and process video frames from
    // media capture using the VideoFrameProcessor class
    class LifiTrackerProcessor
    {
    public:
        static concurrency::task<std::shared_ptr<LifiTrackerProcessor>> CreateAsync(
            std::shared_ptr<VideoFrameProcessor> processor);

        LifiTrackerProcessor(std::shared_ptr<VideoFrameProcessor> processor);

        ~LifiTrackerProcessor(void);

        bool IsTrackingLights(void) const;
		std::vector<Windows::Graphics::Imaging::BitmapBounds> GetLatestLights(void) const;


    protected:
		struct Light {
			char name[20];
			int age;
			double height;
			double weight;
		};

        void ProcessFrame(void);

        //Windows::Media::FaceAnalysis::FaceTracker^            m_faceTracker;
        std::shared_ptr<VideoFrameProcessor>                  m_videoProcessor;

        mutable std::shared_mutex                             m_propertiesLock;
        std::vector<Windows::Graphics::Imaging::BitmapBounds> m_latestLights;

        uint32_t                                              m_numFramesWithoutFaces = 0;

        std::thread                                           m_workerThread;
        bool                                                  m_isRunning = false;
    };
}
