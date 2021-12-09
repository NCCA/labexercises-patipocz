#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Util.h>
#include <iostream>
#include <ngl/Transformation.h>

NGLScene::NGLScene()
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  setTitle("First NGL Patty");
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
  m_project=ngl::perspective(45.0f,
  static_cast<float>(_w)/_h,0.1f,20.0f);
  }


void NGLScene::initializeGL()
{
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::initialize();
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);
  ngl::VAOPrimitives::createSphere("sphere",1.0f,20);
  ngl::ShaderLib::loadShader("Colour","shaders/ColourVertex.glsl",
  "shaders/ColourFragment.glsl");
  ngl::ShaderLib::use("Colour");
  m_view = ngl::lookAt({5,5,5},{0,0,0},{0,1,0});

}

void NGLScene::loadMatrixToShader()
{
  ngl::ShaderLib::setUniform("MVP",m_project*m_view*m_modelTx);
}

void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);
  glPointSize(4);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
  ngl::Transformation tx;
  tx.setPosition(-1,0,0);
  tx.setScale(1,2,1);
  tx.setRotation(40,0,0);
  m_modelTx=tx.getMatrix();
  loadMatrixToShader();
  ngl::VAOPrimitives::draw("sphere");
  tx.reset();
  tx.setPosition(0,0,2);
  m_modelTx=tx.getMatrix();
  loadMatrixToShader();
  ngl::VAOPrimitives::draw(ngl::teapot);
  tx.reset();
  tx.setScale(0.1f,0.1f,0.1f);
  tx.setPosition(0,0,-4);
  m_modelTx=tx.getMatrix();
  loadMatrixToShader();
  ngl::VAOPrimitives::draw(ngl::bunny);


}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space :
      m_win.spinXFace=0;
      m_win.spinYFace=0;
      m_modelPos.set(ngl::Vec3::zero());

  break;
  default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}
