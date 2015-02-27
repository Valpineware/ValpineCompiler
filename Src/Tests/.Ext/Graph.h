#include "../Tests.h"
#include <Graph/Graph.h>
using namespace vc::graph;

namespace ext
{
	Class* addClass(Block &block, const QString &id)
	{
		auto cls = new Class("");
		cls->setId(id);

		return cls;
	}


	ControlStructure* addControlStructure(Block &block, const QString &id, const QString &expression)
	{
		auto cs = new ControlStructure("");
		cs->setName(id);
		cs->setExpression(expression);

		return cs;
	}


	Expression* addExpression(Block &block,  Expression *expression)
	{
		block.appendStatement(expression);
		return expression;
	}
};