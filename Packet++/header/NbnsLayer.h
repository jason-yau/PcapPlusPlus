#ifndef NBNSLAYER_H
#define NBNSLAYER_H

#include "Layer.h"
#include "TLVData.h"

/// @file NbnsLayer.h

/**
 * \namespace pcpp
 * \brief The main namespace for the PcapPlusPlus lib
 */
namespace pcpp {
	/**
	 * @struct nbns_header
	 * Represents the basic NBNS protocol header
	 */
	struct nbns_header
	{
		/** NBNS transaction ID */
		uint16_t transactionId;
		/** NBNS transaction ID */
		uint16_t nmFlags;
	};

	/**
	 * @class NbnsLayer
	 * Represents a NetBIOS Name Service protocol layer
	 * see: https://wiki.wireshark.org/NetBIOS/NBNS
	 */
	class NbnsLayer : public Layer
	{
	  public:
		/**
		 * A constructor that creates the layer from an existing packet raw data
		 * @param[in] data A pointer to the raw data
		 * @param[in] dataLen Size of the data in bytes
		 * @param[in] prevLayer A pointer to the previous layer
		 * @param[in] packet A pointer to the Packet instance where layer will be stored in
		 */
		NbnsLayer(uint8_t* data, size_t dataLen, Layer* prevLayer, Packet* packet);

		/**
		 * @return The transaction ID of this NBNS layer
		 */
		uint16_t getTransactionID() const { getNbnsHeader()->transactionId; }

		/**
		 * @return The header of this NBNS layer
		 */
		nbns_header* getNbnsHeader() const { return (nbns_header*)m_Data; }

		/**
		 * A static method that checks whether a port is considered as a NBNS port
		 * @param[in] port The port number to check
		 * @return True if this is a NBNS port number, false otherwise
		 */
		static inline bool isNbnsPort(uint16_t port);

		/**
		 * A static method that validates the input data
		 * @param[in] data The pointer to the beginning of a byte stream of an NBNS layer
		 * @param[in] dataLen The length of the byte stream
		 * @return True if the data is valid and can represent an NBNS layer
		 */
		static inline bool isDataValid(const uint8_t* data, size_t dataLen);

		/**
		 * Does nothing for this layer (NbnsLayer is always last)
		 */
		void parseNextLayer() {}

		/**
		 * @return The size of @ref nbns_header + size of options
		 */
		size_t getHeaderLen() const { return m_DataLen; }

		/**
		 * Does nothing for this layer
		 */
		void computeCalculateFields() {}

		std::string toString() const;

		OsiModelLayer getOsiModelLayer() const { return OsiModelApplicationLayer; }
	};

	// implementation of inline methods

	inline bool NbnsLayer::isNbnsPort(uint16_t port)
	{
		 return port == 137;
	}

	inline bool NbnsLayer::isDataValid(const uint8_t *data, size_t dataLen)
	{
		return data && dataLen >= sizeof(nbns_header);
	}
}

#endif // NBNSLAYER_H
