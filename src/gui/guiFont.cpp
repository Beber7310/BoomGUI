/*
 * guiFont.cpp
 *
 *  Created on: 9 oct. 2017
 *      Author: Bertrand
 */

#include <guiFont.h>

guiFont::guiFont() {
	_renderer2 = NULL;
	_police2 = NULL;
	_textFont = NULL;
}

guiFont::guiFont(SDL_Renderer *renderer, char* font) {
	_renderer2 = renderer;
	_textFont = NULL;
	_police2 = TTF_OpenFont(font, 30);
	if (!_police2) {
		printf("TTF_OpenFont Error: %s\n", SDL_GetError());

	}
	initFont();

}

guiFont::~guiFont() {
	// TODO Auto-generated destructor stub
}

int guiFont::glyph2Index(char* pTextS, int* idx, int* offset) {
	*idx = -1;
	unsigned char* pTextU = (unsigned char*) pTextS;

	if (pTextU[0] == 0) {
		return 0; //END OF STRING
	} else if (pTextU[0] < 0x20) {
		*offset += 1;
	} else if (pTextU[0] < 0x7F) {
		*offset += 1;
		*idx = pTextU[0] - 0x20;
	} //0x60
	else if (pTextU[0] == 0xc2) {
		if ((pTextU[1] >= 0xA0) && (pTextU[1] < 0xC0)) {
			*offset += 2;
			*idx = pTextU[1];
			*idx -= 0x40;
		}
	} else if (pTextU[0] == 0xc3) {
		if ((pTextU[1] >= 0x80) && (pTextU[1] < 0xC0)) {
			*offset += 2;
			*idx = pTextU[1];
		}
	} else {
		*offset += 1;
	}
	return 1;

}

int guiFont::computeTextureSize() {
	int w, h;
	int finalW = 0;
	int finalh =  TTF_FontHeight(_police2);
	int idx;
	int offset = 0;

	char str_tmp[4];
	for (int ii = 1; ii < 0x7f; ii++) {
		str_tmp[0] = ii;
		str_tmp[1] = 0;

		glyph2Index(str_tmp, &idx, &offset);
		if (idx >= 0) {
			TTF_SizeUTF8(_police2, str_tmp, &w, &h);
			finalW += w;
			if (finalW > 511) {
				finalW = w;
				finalh += TTF_FontHeight(_police2);
			}
		}
	}
	for (int ii = 0xA0; ii < 0xC0; ii++) {
		str_tmp[0] = 0xC2;
		str_tmp[1] = ii;
		str_tmp[2] = 0;

		glyph2Index(str_tmp, &idx, &offset);
		if (idx >= 0) {
			TTF_SizeUTF8(_police2, str_tmp, &w, &h);
			finalW += w;
			if (finalW > 511) {
				finalW = w;
				finalh += TTF_FontHeight(_police2);
			}
		}
	}
	for (int ii = 0x80; ii < 0xC0; ii++) {
		str_tmp[0] = 0xC3;
		str_tmp[1] = ii;
		str_tmp[2] = 0;

		glyph2Index(str_tmp, &idx, &offset);
		if (idx >= 0) {
			TTF_SizeUTF8(_police2, str_tmp, &w, &h);
			finalW += w;
			if (finalW > 511) {
				finalW = w;
				finalh += TTF_FontHeight(_police2);
			}
		}
	}
	printf("    <> texture font height %i\n", finalW);
	return finalh;

}

/*
 void guiFont::initFont() {
 char str_tmp[4];
 SDL_Texture *_textTmp;
 SDL_Rect _srcSize;
 int fontHeight;
 int lastX = 0;
 int idx;
 int offset = 0;

 printf("<>Building Font\n");
 fontHeight = TTF_FontHeight(_police2);

 //Make a target texture to render too
 _textFont = SDL_CreateTexture(_renderer2, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, computeTextureSize(), fontHeight);
 SDL_Color couleurTexte = { 255, 255, 255, 255 };

 //Now render to the texture
 SDL_SetRenderTarget(_renderer2, _textFont);
 SDL_SetRenderDrawColor(_renderer2, 0x00, 0x00, 0x00, 0x00);
 SDL_RenderClear(_renderer2);
 SDL_SetRenderDrawBlendMode(_renderer2, SDL_BLENDMODE_BLEND);

 for (int ii = 1; ii < 0x7f; ii++) {
 str_tmp[0] = ii;
 str_tmp[1] = ii >> 8;
 str_tmp[2] = 0;

 glyph2Index(str_tmp, &idx, &offset);
 if (idx >= 0) {
 SDL_Surface* texteAlb = TTF_RenderUTF8_Blended(_police2, str_tmp, couleurTexte);
 _textTmp = SDL_CreateTextureFromSurface(_renderer2, texteAlb);
 SDL_QueryTexture(_textTmp, NULL, NULL, &_glyphSize[idx].w, &_glyphSize[idx].h);
 _glyphSize[idx].x = lastX;
 _glyphSize[idx].y = 0;
 lastX += _glyphSize[idx].w;

 _srcSize.x = 0;
 _srcSize.y = 0;
 _srcSize.w = _glyphSize[idx].w;
 _srcSize.h = _glyphSize[idx].h;
 SDL_SetTextureBlendMode(_textTmp, SDL_BLENDMODE_NONE);
 SDL_RenderCopy(_renderer2, _textTmp, &_srcSize, &_glyphSize[idx]);

 SDL_DestroyTexture(_textTmp);
 SDL_FreeSurface(texteAlb);
 }
 }

 //Detach the texture
 SDL_SetRenderTarget(_renderer2, NULL);
 SDL_SetTextureBlendMode(_textFont, SDL_BLENDMODE_ADD);

 }*/

void guiFont::initFont() {
	char str_tmp[4];
//	SDL_Texture *_textTmp;
//	SDL_Rect _srcSize;
	int fontHeight;
	int lastX = 0;
	int lastY = 0;
	//int idx;
	//int offset = 0;

	printf("<>Building Font\n");


	//Make a target texture to render too
	_textFont = SDL_CreateTexture(_renderer2, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,512 , computeTextureSize());
	//SDL_Color couleurTexte = { 255, 255, 255, 255 };

	//Now render to the texture
	SDL_SetRenderTarget(_renderer2, _textFont);
	SDL_SetRenderDrawColor(_renderer2, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(_renderer2);
	SDL_SetRenderDrawBlendMode(_renderer2, SDL_BLENDMODE_BLEND);

	for (int ii = 0; ii < 0x7f; ii++) {
		str_tmp[0] = ii;
		str_tmp[1] = 0;
		createGliph(str_tmp, &lastX, &lastY);
	}
	for (int ii = 0xA0; ii < 0xC0; ii++) {
		str_tmp[0] = 0xC2;
		str_tmp[1] = ii;
		str_tmp[2] = 0;
		createGliph(str_tmp, &lastX, &lastY);
	}
	for (int ii = 0x80; ii < 0xC0; ii++) {
		str_tmp[0] = 0xC3;
		str_tmp[1] = ii;
		str_tmp[2] = 0;
		createGliph(str_tmp, &lastX, &lastY);
	}

	//Detach the texture
	SDL_SetRenderTarget(_renderer2, NULL);
	SDL_SetTextureBlendMode(_textFont, SDL_BLENDMODE_ADD);
/*
	SDL_Rect dstSize;
	dstSize.x=0;
	dstSize.y=0;
	dstSize.w=512;
	dstSize.h=computeTextureSize();

	SDL_RenderCopy(_renderer2, _textFont, NULL,&dstSize);
	SDL_RenderPresent(_renderer2);
	while(1);*/
}

int guiFont::createGliph(char * str_tmp, int *lastX, int *lastY) {

	int idx;
	int offset = 0;
	SDL_Color couleurTexte = { 255, 255, 255, 255 };
	SDL_Texture *_textTmp;
	SDL_Rect _srcSize;

	glyph2Index(str_tmp, &idx, &offset);
	if (idx >= 0) {
		SDL_Surface* texteAlb = TTF_RenderUTF8_Blended(_police2, str_tmp, couleurTexte);
		_textTmp = SDL_CreateTextureFromSurface(_renderer2, texteAlb);
		SDL_QueryTexture(_textTmp, NULL, NULL, &_glyphSize[idx].w, &_glyphSize[idx].h);

		_glyphSize[idx].x = *lastX;
		_glyphSize[idx].y = *lastY;

		if((_glyphSize[idx].x+_glyphSize[idx].w)>512)
		{
			_glyphSize[idx].x=0;
			_glyphSize[idx].y+= TTF_FontHeight(_police2);
			*lastY =_glyphSize[idx].y;
		}

		_srcSize.x = 0;
		_srcSize.y = 0;
		_srcSize.w = _glyphSize[idx].w;
		_srcSize.h = _glyphSize[idx].h;

		SDL_SetTextureBlendMode(_textTmp, SDL_BLENDMODE_NONE);
		SDL_RenderCopy(_renderer2, _textTmp, &_srcSize, &_glyphSize[idx]);

		SDL_DestroyTexture(_textTmp);
		SDL_FreeSurface(texteAlb);

		*lastX = _glyphSize[idx].x+_glyphSize[idx].w;

	}

	return 0;
}

void guiFont::print(char* str, int x, int y) {
	SDL_Rect _dstSize;
	int idx;
	int offset = 0;

	if (!(str))
		return;

	_dstSize.x = x;
	_dstSize.y = y;
	while (glyph2Index(str + offset, &idx, &offset)) {
		if (idx > 0) {
			_dstSize.w = _glyphSize[idx].w;
			_dstSize.h = _glyphSize[idx].h;
			SDL_RenderCopy(_renderer2, _textFont, &_glyphSize[idx], &_dstSize);
			_dstSize.x += _glyphSize[idx].w;
		}
		if (str[offset] == '\n') {
			_dstSize.x = x;
			_dstSize.y += _glyphSize[1].h;
		}
		if (str[offset] == ' ') {
			_dstSize.x += _glyphSize[':'].w;
		}

	}

}

