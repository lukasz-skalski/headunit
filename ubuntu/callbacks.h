#pragma once

#include <atomic>

#include "main.h"
#include "audio.h"
#include "command_server.h"

#include <asoundlib.h>

class VideoOutput;
class AudioOutput;


class DesktopEventCallbacks : public IHUConnectionThreadEventCallbacks {
        std::unique_ptr<VideoOutput> videoOutput;
        std::unique_ptr<AudioOutput> audioOutput;

        MicInput micInput;
public:
        DesktopEventCallbacks();
        ~DesktopEventCallbacks();

        virtual int MediaPacket(int chan, uint64_t timestamp, const byte * buf, int len) override;
        virtual int MediaStart(int chan) override;
        virtual int MediaStop(int chan) override;
        virtual void MediaSetupComplete(int chan) override;
        virtual void DisconnectionOrError() override;
        virtual void CustomizeOutputChannel(int chan, HU::ChannelDescriptor::OutputStreamChannel& streamChannel) override;
        virtual void AudioFocusRequest(int chan, const HU::AudioFocusRequest& request) override;
        virtual void VideoFocusRequest(int chan, const HU::VideoFocusRequest& request) override;

        void VideoFocusHappened(bool hasFocus, bool unrequested);

        std::atomic<bool> connected;
        std::atomic<bool> videoFocus;
        std::atomic<bool> audioFocus;
};

class DesktopCommandServerCallbacks : public ICommandServerCallbacks
{
public:
    DesktopCommandServerCallbacks();

    DesktopEventCallbacks* eventCallbacks = nullptr;

    virtual bool IsConnected() const override;
    virtual bool HasAudioFocus() const override;
    virtual bool HasVideoFocus() const override;
    virtual void TakeVideoFocus() override;
    virtual std::string GetLogPath() const override;
};
