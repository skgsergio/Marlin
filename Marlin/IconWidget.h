#ifndef ICON_WIDGET_H
#define ICON_WIDGET_H

#include "Icon.h"
#include "Observer.h"

#include "GuiPainter.h"

namespace screen
{
	template <typename T>
		class IconWidget : public Icon, public Observer<T>
	{
		public:
			IconWidget(Size const & size, const unsigned char* bitmap, const unsigned char * focused_bitmap, const char * text, Subject<T> * model);
			virtual ~IconWidget();

			void update(T value);

			void draw(uint8_t x, uint8_t y, bool focused = false);
			virtual void show();

		private:
			T m_value;
	};

	template <typename T>
	IconWidget<T>::IconWidget(Size const & size, const unsigned char* bitmap, const unsigned char * focused_bitmap, const char * text, Subject<T> * model)
		: Icon(size, bitmap, focused_bitmap, text)
		, Observer<T>(model)
	{ }

	template <typename T>
	IconWidget<T>::~IconWidget()
	{ }

	template <typename T>
	void IconWidget<T>::update(T value)
	{
		m_value = value;
	}

	template <typename T>
	void IconWidget<T>::draw(uint8_t x, uint8_t y, bool focused)
	{
		painter.setColorIndex(1);
		painter.drawBitmap(x, y, m_size.width, m_size.height, (focused) ? m_focused_bitmap : m_bitmap);
		
		if(focused)
		{
			painter.setColorIndex(0);
		}
		uint8_t margin = 26;
		if(m_value > 99)
		{
			margin = 20;
		}
		else if(m_value < 10 && m_value >= 0)
		{
			margin = 32;
		}
		painter.setPrintPos(x + margin, y + (m_size.height / 2) - (max_font_height / 2));
		painter.print(painter.itostr3left((int)m_value));
		painter.print("\xb0");
	}

	template <typename T>
	void IconWidget<T>::show()
	{
		this->m_model->attach(this);
		this->connect();
	}
}

#endif //ICON_WIDGET_H