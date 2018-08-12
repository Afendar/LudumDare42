#pragma once

#include "Box.h"

class Order
{
	public:
		Order(Article article);
		~Order();

		void update(float dt);

		bool isCanceled();
		bool isCompleted();

		void setCompleted();

		int getCancelBarSize();

		Article getArticle() const;

	private:

		Article m_article;
		int m_timeToPrepare;
		float m_timer;

		bool m_canceled, m_red, m_completed;
};