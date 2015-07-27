//
//  ControlPacket.h
//  libraries/networking/src/udt
//
//  Created by Stephen Birarda on 2015-07-24.
//  Copyright 2015 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#pragma once

#ifndef hifi_ControlPacket_h
#define hifi_ControlPacket_h

#include <vector>

#include "BasePacket.h"
#include "Packet.h"

namespace udt {
    
class ControlPacket : public BasePacket {
    Q_OBJECT
public:
    using TypeAndSubSequenceNumber = uint32_t;
    using ControlPacketPair = std::pair<std::unique_ptr<ControlPacket>, std::unique_ptr<ControlPacket>>;
    
    enum Type : uint16_t {
        ACK,
        ACK2,
        NAK,
        PacketPair
    };
    
    static std::unique_ptr<ControlPacket> create(Type type, qint64 size = -1);
    static ControlPacketPair createPacketPair(quint64 timestamp);
    
    static qint64 localHeaderSize(); // Current level's header size
    virtual qint64 totalHeadersSize() const; // Cumulated size of all the headers
    
    Type getType() const { return _type; }
    
private:
    ControlPacket(Type type);
    ControlPacket(Type type, qint64 size);
    ControlPacket(quint64 timestamp);
    ControlPacket(ControlPacket&& other);
    ControlPacket(const ControlPacket& other) = delete;
    
    ControlPacket& operator=(ControlPacket&& other);
    ControlPacket& operator=(const ControlPacket& other) = delete;
    
    Type _type;
};

} // namespace udt


#endif // hifi_ControlPacket_h
