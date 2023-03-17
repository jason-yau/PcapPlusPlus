#ifndef ECATLAYER_H
#define ECATLAYER_H

#include "Layer.h"

/**
 * \namespace pcpp
 * \brief The main namespace for the PcapPlusPlus lib
 */
namespace pcpp {
	/**
	 * @struct ecat_header
	 * Represents the basic ECAT protocol header
	 */
	struct ecat_header {
		uint16_t data;
	};

	/**
	 * @class EcatLayer
	 * Represents a ECAT protocol layer
	 */
	class EcatLayer : public Layer
	{
	public:
		/**
		 * A constructor that creates the layer from an existing packet raw data
		 * @param[in] data A pointer to the raw data
		 * @param[in] dataLen Size of the data in bytes
		 * @param[in] prevLayer A pointer to the previous layer
		 * @param[in] packet A pointer to the Packet instance where layer will be stored in
		 */
		EcatLayer(uint8_t* data, size_t dataLen, Layer* prevLayer, Packet* packet);

		/**
		 * @return The header of this ECAT layer
		 */
		ecat_header* getEcatHeader() const { return (ecat_header*)m_Data; }

		/**
		 * Currently identifies the following next layers: PadBytesLayer
		 */
		void parseNextLayer();

		/**
		 * Does nothing for this layer
		 */
		void computeCalculateFields(){}

		std::string toString() const;

		/**
		 * @return Same as getHeaderLen
		 */
		uint16_t length() const;

		/**
		 * @return The size of @ref nbns_header + size of options
		 */
		size_t getHeaderLen() const override { return length(); }

		OsiModelLayer getOsiModelLayer() const override { return OsiModelDataLinkLayer; }

		/**
		 * A static method that checks whether a port is considered as a ECAT port
		 * @param[in] port The port number to check
		 * @return True if this is a ECAT port number, false otherwise
		 */
		static inline bool isEcatPort(uint16_t port);

		/**
		 * A static method that validates the input data
		 * @param[in] data The pointer to the beginning of a byte stream of an ECAT layer
		 * @param[in] dataLen The length of the byte stream
		 * @return True if the data is valid and can represent an ECAT layer
		 */
		static inline bool isDataValid(const uint8_t *data, size_t length);
	};

	// implementation of inline methods of EcatLayer

	inline bool EcatLayer::isEcatPort(uint16_t port)
	{
		return port == 0x88a4;
	}

	inline bool EcatLayer::isDataValid(const uint8_t *data, size_t length)
	{
		return data && length >= sizeof(ecat_header);
	}

	/**
	 * @class PadBytesLayer
	 */
	class PadBytesLayer: public Layer
	{
	public:
		/**
		 * A constructor that creates the layer from an existing packet raw data
		 * @param[in] data A pointer to the raw data
		 * @param[in] dataLen Size of the data in bytes
		 * @param[in] prevLayer A pointer to the previous layer
		 * @param[in] packet A pointer to the Packet instance where layer will be stored in
		 */
		PadBytesLayer(uint8_t* data, size_t dataLen, Layer* prevLayer, Packet* packet);

		/**
		 * Does nothing for this layer (NbnsLayer is always last)
		 */
		void parseNextLayer(){}

		/**
		 * Does nothing for this layer
		 */
		void computeCalculateFields(){}

		/**
		 * @return The size of @ref PadBytesLayer
		 */
		size_t getHeaderLen() const override { return m_DataLen; }

		OsiModelLayer getOsiModelLayer() const override { return OsiModelDataLinkLayer; }

		std::string toString() const;
	};

}


#endif // ECATLAYER_H
