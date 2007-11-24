#pragma once

#include "XMLUtils.h"

class ŃColladaIDREFArray : public CAutoContainer<ŃColladaIDREFArray>
{
	std::vector<SStrng>  body;
	std::vector<xmlChar> content;
public:
	ŃColladaIDREFArray(void);
public:
	const std::vector<SStrng> &GetArray() const;
	virtual ~ŃColladaIDREFArray(void);
	void BuildContent(){};
	static const xmlChar *GetName() { return _X"IDREF_array"; };
	static ŃColladaIDREFArray *CreateInstance( xmlNode *node );
};
