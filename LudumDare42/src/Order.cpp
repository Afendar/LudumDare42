#include "Order.h"
#include "Game.h"

#include <iostream>

Order::Order(Article article) :
	m_article(article),
	m_timeToPrepare(15),
	m_canceled(false),
	m_red(false),
	m_timer(0),
	m_completed(false)
{

}

Order::~Order()
{

}

void Order::update(float dt)
{
	m_timer += dt;
	if (m_timer >= m_timeToPrepare - 2)
	{
		m_red = true;
	}
	if (m_timer > m_timeToPrepare)
	{
		m_canceled = true;
		//std::cout << "Order Canceled: " << m_timer << std::endl;
	}
}

int Order::getCancelBarSize()
{
	return 22 - (22 / m_timeToPrepare) * m_timer;
}

bool Order::isCanceled()
{
	return m_canceled;
}

bool Order::isCompleted()
{
	return m_completed;
}

void Order::setCompleted()
{
	m_completed = true;
}

Article Order::getArticle() const
{
	return m_article;
}