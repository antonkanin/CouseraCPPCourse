#pragma once

#include "node.h"

#include <memory>
#include <iostream>
#include "Node.h"

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);
