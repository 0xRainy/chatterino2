#pragma once

#include "channel.hpp"
#include "concurrentmap.hpp"
#include "ircmanager.hpp"

namespace chatterino {
namespace twitch {

class TwitchChannel : public Channel
{
    QTimer *liveStatusTimer;

public:
    explicit TwitchChannel(IrcManager &ircManager, const QString &channelName,
                           bool _isSpecial = false);
    ~TwitchChannel();

    void reloadChannelEmotes();

    bool isEmpty() const override;
    bool canSendMessage() const override;
    void sendMessage(const QString &message) override;

    const QString subscriptionURL;
    const QString channelURL;
    const QString popoutPlayerURL;

    void setRoomID(const QString &_roomID);
    boost::signals2::signal<void()> roomIDchanged;
    boost::signals2::signal<void()> onlineStatusChanged;

    QString roomID;
    bool isLive;
    QString streamViewerCount;
    QString streamStatus;
    QString streamGame;
    QString streamUptime;

    const std::shared_ptr<EmoteMap> bttvChannelEmotes;
    const std::shared_ptr<EmoteMap> ffzChannelEmotes;

private:
    void setLive(bool newLiveStatus);
    void refreshLiveStatus();

    IrcManager &ircManager;

    bool isSpecial;
};

}  // namespace twitch
}  // namespace chatterino