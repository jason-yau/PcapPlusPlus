#define LOG_MODULE PacketLogModuleNbnsLayer

#include "NbnsLayer.h"

namespace pcpp {

NbnsLayer::NbnsLayer(uint8_t* data, size_t dataLen, Layer* prevLayer, Packet* packet) : Layer(data, dataLen, prevLayer, packet)
{
	m_Protocol = NBNS;
}

std::string NbnsLayer::toString() const
{
	return "NetBIOS Name Service layer";
}

}

