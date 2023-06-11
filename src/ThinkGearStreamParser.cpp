#include "ThinkGearStreamParser.h"
#include "ThinkGearPayloadParser.h"
#include <iostream>
#include <memory>
namespace libThinkGearCpp {
ThinkGearStreamParser::ThinkGearStreamParser(ParserTypes type, ThinkGear *tg)
: _type{type}, _tg{tg}
{
    init();
}

ThinkGearStreamParser::~ThinkGearStreamParser()
{

}

void ThinkGearStreamParser::init()
{
    switch (_type) {
        case( ParserTypes::Packets ):
            _status = ParserStatus::Idle;
            break;
        case( ParserTypes::TwoByteRaw ):
            _status = ParserStatus::WaitHigh;
            break;
        default:
            _status = ParserStatus::Null;
    }
}

void ThinkGearStreamParser::parseByte(unsigned char byte)
{
    if (!isInited()) return;
    _lastByte = byte;
    //std::cout << "=====================" << std::endl;
    //std::cout << "Received byte: " << std::hex << (int) byte << std::endl;
    switch (_status) {
        case( ParserStatus::Idle ): receiveSyncByte(); break;
        case( ParserStatus::Sync ): receiveSyncByte(); break;
        case( ParserStatus::PayloadLength ): initPayload(); break;
        case( ParserStatus::Payload ): writePayload(); break;
        case( ParserStatus::Checksum ): checkPayload(); break;
        case( ParserStatus::WaitHigh ): twoByteRawInit(); break;
        case( ParserStatus::WaitLow ): twoByteRawParse(); break;
    }
    //std::cout << "=====================" << std::endl;
    
}

void ThinkGearStreamParser::receiveSyncByte()
{
    if (_lastByte != ParserCodes::SyncByte) {
        reset();
        return;
    }
    
    switch (_status) { 
        case ( ParserStatus::Idle ): _status = ParserStatus::Sync; break;
        case ( ParserStatus::Sync ): _status = ParserStatus::PayloadLength; break;
        default: reset(); return;
    }
}

void ThinkGearStreamParser::reset()
{
    _payload.release();
    _status = ParserStatus::Idle;
}

void ThinkGearStreamParser::initPayload()
{ 
    if (_lastByte > ParserCodes::SyncByte) {
        _receive_status = ReceiveStatus::PlenghtTooLarge;
        reset();
        return;
    } else if (_lastByte == ParserCodes::SyncByte) {
        _receive_status = ReceiveStatus::InvalidWithSync;
        reset();
        return;
    }
    _payload = std::make_unique<ThinkGearPayload>(_lastByte);
    _status = ParserStatus::Payload;
    
}

void ThinkGearStreamParser::writePayload()
{
    _payload->writeByte(_lastByte);
    if (_payload->completed()) _status = ParserStatus::Checksum;
}

void ThinkGearStreamParser::checkPayload()
{
    _payload->setChecksum(_lastByte);
    if (_payload->isValid()) {
        _receive_status = ReceiveStatus::Success;
        parsePayload();
    } else {
        _receive_status = ReceiveStatus::ChecksumFailed;
    }
    reset();
}

void ThinkGearStreamParser::parsePayload()
{
    ThinkGearPayloadParser payloadParser(std::move(_payload), _tg);
    reset();
    
}

void ThinkGearStreamParser::twoByteRawInit()
{
    _payload = std::make_unique<ThinkGearPayload>(4);
    _payload->writeByte(0x80);
    _payload->writeByte(0x02);
    _payload->writeByte(_lastByte);
}

void ThinkGearStreamParser::twoByteRawParse()
{
    _payload->writeByte(_lastByte);
}

} // namespace libThinkGearCpp
