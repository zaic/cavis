#pragma once

#include <cstdio>
#include "buffer/buffer.h"
#include "config/config.h"
#include "cut/cut.h"

/**
 * @brief Хреновина, обеспечивающее взаимодействие между осями
 */
class Visualizzzator {
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
	Cut2D *cut;

	/**
	 * @brief Конструктор из конфига и отображения
	 * @param _config конфиг
	 * @param _cut маппер из реального пространства в логическое
	 */
	Visualizzzator(Config *_config, Cut2D *_cut);

	/**
	 * @brief Всеразрушающий деструктор
	 */
	~Visualizzzator();

	/**
	 * @brief Совершает непотребство с буфером, т.е. рисует на нём
	 * @param buffer Буфер, на котором будет отрисовываться картинка
	 */
	void operator()(GraphicBuffer& buffer);
};
