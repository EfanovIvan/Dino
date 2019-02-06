/*
 * MainGero.cpp
 *
 *  Created on: 4 янв. 2019 г.
 *      Author: ivan
 */

#include <MainGero.hpp>
#include <EntityState.hpp>
#include <IdleState.hpp>
	MainGero::MainGero(sf::Texture& l_texture, b2World& l_world)
								:m_SelectAnim(l_texture)
								,world(l_world)
								,m_EntityState(new IdleState())

{
		name = new std::string("dino");
		m_SelectAnim.load("XMLfiles/DinoRectangle.xml");
		m_OnGround = false;
		stateID = EntityState::GraphicState::IDLE;

}

void MainGero::handleEvent(const sf::Event& event)
{
	EntityState* state = m_EntityState->handleEvent(*this,event);
	if( state != nullptr)
	{
		delete m_EntityState;
		m_EntityState = state;
		stateID = m_EntityState->state();
	}



}
void MainGero::update(float time)
{

	b2Vec2  vecBody = body->GetPosition();
		int x, y;
		x = converter::metersToPixels(vecBody.x);
		y = converter::metersToPixels(vecBody.y);
	for (b2ContactEdge* edge = body->GetContactList();
											edge; edge = edge->next)
		{
			if(edge->contact->IsTouching() &&
					body->GetLinearVelocity().y > -1
					&& stateID == EntityState::GraphicState::JUMP
					)
			{
				idle();
				m_OnGround = true;
				m_EntityState = new IdleState;
				stateID = m_EntityState->state();

				//m_EntityState = new IdleState;
			}
		}



//		vecBody.y +=  converter::pixelsToMeters(80);
//		vecBody.x += converter::pixelsToMeters(150);

			x -= m_Rect.width/2;
			y -= m_Rect.height/2;
			delta = m_Rect.left;
			 m_Rect.left = x;
			 m_Rect.top = y;


			 delta = m_Rect.left - delta;
			 m_Direction = direct(delta);

	m_SelectAnim.animationOutput(*this, time);
	viewGero.setCenter(m_Rect.left, m_Rect.top);

}
void MainGero::creatBodyBox2d(sf::Rect<float> l_Rect)
{
	m_Rect = l_Rect;
	using converter::pixelsToMeters;
	bodyDef.position.Set(pixelsToMeters<double>(m_Rect.left+m_Rect.width/2),
						pixelsToMeters<double>(m_Rect.top+m_Rect.height/2));

	bodyDef.type = b2_dynamicBody;

		b2shape.SetAsBox(pixelsToMeters<double>(m_Rect.width/2.0),
						 pixelsToMeters<double>(m_Rect.height/2.0));


		m_FixtureDef.density = 1;
		m_FixtureDef.friction = 0.1;
		m_FixtureDef.restitution= 0;
		m_FixtureDef.shape = &b2shape;

		body = world.CreateBody(&bodyDef);
		body->CreateFixture(&m_FixtureDef);
		//body -> SetUserData((void*)&m_nameGero);
		std::cout << " create" << std::endl;

}

sf::View& MainGero::getGeroView()
{
	sf::Vector2f tempVec{0.0,0.0};
	tempVec.x = m_Rect.left;
	tempVec.y = m_Rect.top;
	if(m_Rect.left < 500.0 )
		tempVec.x = 500;
	//viewGero.setCenter(500, m_Rect.top);
	if(m_Rect.top > 425)
			tempVec.y = 425;
	if(m_Rect.left > 5000)
			tempVec.x = 5000;
	//viewGero.setCenter(m_Rect.left, 500);
	viewGero.setCenter(tempVec);
	return viewGero;

}

void MainGero::walk()
{
	body->SetLinearVelocity(b2Vec2(converter::pixelsToMeters(150.f),
				converter::pixelsToMeters(9.8f)));
}

void MainGero::idle()
{
	body->SetLinearVelocity(b2Vec2(converter::pixelsToMeters(0.f),
				converter::pixelsToMeters(9.8f)));
}
void MainGero::walkLeft()
{
	body->SetLinearVelocity(b2Vec2(converter::pixelsToMeters(-150.f),
				converter::pixelsToMeters(9.8f)));
	//m_b2Body->ApplyForceToCenter(b2Vec2(converter::pixelsToMeters(40),0),true);

}
void MainGero::jump()
{

	if(m_OnGround)
	{
		m_OnGround = false;
		float x = body->GetLinearVelocity().x;
		body->SetLinearVelocity(b2Vec2(x,
						converter::pixelsToMeters(-300.f)));

		//setOnGround(false);
		//m_SoundJump.play();
	}
}
void MainGero::runLeft()
{
	body->SetLinearVelocity(b2Vec2(converter::pixelsToMeters(-310.f),
						converter::pixelsToMeters(9.8f)));
}
void MainGero::runRight()
{
	body->SetLinearVelocity(b2Vec2(converter::pixelsToMeters(310.f),
					converter::pixelsToMeters(9.8f)));
}

bool MainGero::direct(float dir)
{
	static bool b = true;
	if(dir == 0) return b;
	dir > 0 ? b = true : b = false;
	return b;
}





