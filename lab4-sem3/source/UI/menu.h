#pragma once

#include <string>
#include <iostream>
#include <cstdio>

#include "../Graph.h"
#include "../WeightEdge.h"
#include "../ConnectionPoint.h"
#include "../containers/SmartPtrLinkedListSequence.h"
#include "GraphOutput.h"
#include "GraphInput.h"
#include "IntInput.h"
#include "WordInput.h"
#include "../GraphAlgorithms.h"

void EdgesInput(shared_ptr<Graph<ConnectionPoint, double>> graphPointer, GraphOutput<ConnectionPoint>& out);

void VerteciesInput(shared_ptr<Graph<ConnectionPoint, double>> graphPointer, GraphOutput<ConnectionPoint>& out);

int graphOptionInput();

void graphEdit(shared_ptr<Graph<ConnectionPoint, double>> graphPointer, GraphOutput<ConnectionPoint>& out);

int menu();