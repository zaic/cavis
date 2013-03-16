#pragma once

#include <cstdio>
#include "buffer/buffer.h"
#include "config/config.h"
#include "renderer/renderer.h"
#include "common.h"

#include <iostream>
using namespace std;

/**
 * @brief Хреновина, обеспечивающее взаимодействие между осями
 */
class Visualizzzator
{
	Visualizzzator();
	Visualizzzator(const Visualizzzator& );
	Visualizzzator& operator=(const Visualizzzator& );

public:
	/**
	 * @brief Публичный указатель на конфигурацияю
	 */
	Config *config;

	/**
	 * @brief Публичный указатель на класс отображения логического пространства в буфер экрана
	 */
	Renderer *renderer;

	/**
	 * @brief Публичный указатель на окно для рисования
	 */
	GraphicBuffer* buffer;

	/**
	 * @brief Конструктор из конфига и отображения
	 * @param _config конфиг
	 * @param _cut маппер из реального пространства в логическое
	 */
	Visualizzzator(Config *_config, Renderer *_renderer);

	/**
	 * @brief Всеразрушающий деструктор
	 */
	~Visualizzzator();

	/**
	 * @brief Совершает непотребство с буфером, т.е. рисует на нём
	 * @param buffer Буфер, на котором будет отрисовываться картинка
	 */
	void draw();
};
