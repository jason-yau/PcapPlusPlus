#define LOG_MODULE PacketLogModuleEcatLayer

#include "EcatLayer.h"
#include <iostream>

namespace pcpp {

EcatLayer::EcatLayer(uint8_t* data, size_t dataLen, Layer* prevLayer, Packet* packet)
	: Layer(data, dataLen, prevLayer, packet)
{
	m_Protocol = 0x88a4;
}

void EcatLayer::parseNextLayer()
{
	int layerLen = length();
	if (layerLen < m_DataLen)
	{
        size_t length = m_DataLen - layerLen;
        uint8_t *data = m_Data + layerLen;
        m_NextLayer = new PadBytesLayer(data, length, this, m_Packet);
    }
}

std::string EcatLayer::toString() const
{
    return "EtherCAT Layer, Data length: " + std::to_string(length()) + " bytes";
}

uint16_t EcatLayer::length() const
{
	return (getEcatHeader()->data & (1 << 11) - 1) + sizeof(ecat_header);
}

PadBytesLayer::PadBytesLayer(uint8_t *data, size_t dataLen, Layer *prevLayer, Packet *packet)
	: Layer(data, dataLen, prevLayer, packet)
{
	m_Protocol = 0x88a4;
}

std::string PadBytesLayer::toString() const
{
	std::string str;
	for (int i = 0; i < m_DataLen; ++i)
	{
		char buf[3];
		sprintf(buf, "%02x", m_Data[i]);
		str += buf;
    }
	return "Pad bytes: " + str;
}

}
