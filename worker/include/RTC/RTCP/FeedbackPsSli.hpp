#ifndef MS_RTC_RTCP_FEEDBACK_SLI_HPP
#define MS_RTC_RTCP_FEEDBACK_SLI_HPP

#include "common.hpp"
#include "RTC/RTCP/FeedbackPs.hpp"

/* RFC 4585
 * Slice Loss Indication (SLI)
 *
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |            First        |        Number           | PictureID |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

namespace RTC { namespace RTCP
{
	class SliItem
		: public FeedbackItem
	{
	private:
		struct Header
		{
			uint32_t compact;
		};

	public:
		static const FeedbackPs::MessageType MessageType = FeedbackPs::SLI;

	public:
		static SliItem* Parse(const uint8_t* data, size_t len);

	public:
		explicit SliItem(Header* header);
		explicit SliItem(SliItem* item);
		SliItem(uint16_t first, uint16_t number, uint8_t pictureId);
		virtual ~SliItem() {};

		uint16_t GetFirst() const;
		void SetFirst(uint16_t first);
		uint16_t GetNumber() const;
		void SetNumber(uint16_t number);
		uint8_t GetPictureId() const;
		void SetPictureId(uint8_t pictureId);

	/* Virtual methods inherited from FeedbackItem. */
	public:
		virtual void Dump() const override;
		virtual size_t Serialize(uint8_t* buffer) override;
		virtual size_t GetSize() const override;

	private:
		Header* header = nullptr;
		uint16_t first;
		uint16_t number;
		uint8_t pictureId;
	};

	// Sli packet declaration.
	typedef FeedbackPsItemPacket<SliItem> FeedbackPsSliPacket;

	/* Inline instance methods. */

	inline
	size_t SliItem::GetSize() const
	{
		return sizeof(Header);
	}

	inline
	uint16_t SliItem::GetFirst() const
	{
		return this->first;
	}

	inline
	void SliItem::SetFirst(uint16_t first)
	{
		this->first = first;
	}

	inline
	uint16_t SliItem::GetNumber() const
	{
		return this->number;
	}

	inline
	void SliItem::SetNumber(uint16_t number)
	{
		this->number = number;
	}

	inline
	uint8_t SliItem::GetPictureId() const
	{
		return this->pictureId;
	}

	inline
	void SliItem::SetPictureId(uint8_t pictureId)
	{
		this->pictureId = pictureId;
	}
}}

#endif
