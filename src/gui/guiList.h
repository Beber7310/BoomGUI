/*
 * guiList.h
 *
 *  Created on: 8 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUILIST_H_
#define SRC_GUILIST_H_

#include "guiBase.h"


class guiList : public guiBase
{

public:
  guiList ();
  virtual
  ~guiList ();

  void render ();
  void event(int x,int y,int button);

  int _offset1; //
  int _offset2; //
  int _contentHeight;
  int _firstYmousse;

  int dbg_spd;
  int dbg_pos;
};

#endif /* SRC_GUILIST_H_ */
