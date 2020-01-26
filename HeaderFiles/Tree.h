#pragma once
#include <cmath>
#include <cstdlib>

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "HeartDiseaseData.h"

constexpr float EPS = 1e-7;

class Node
{
public:
	virtual ~Node() {};
	virtual shortInt classify(HeartDiseaseData::Set& sample) = 0;
	virtual void print(std::ostream& os, size_t level) = 0;
};

class TerminalNode : public Node {
public:
	TerminalNode(const shortInt clazz);

	shortInt classify(HeartDiseaseData::Set& sample);

	void print(std::ostream& os, size_t level);

private:
	shortInt clazz;
};

/// inner node that makes a decision.
class InnerNode : public Node {
public:
	InnerNode(size_t attribute, shortInt&& clazz, std::unordered_map<shortInt, std::unique_ptr<Node>>&& branches)
		: attribute(attribute), clazz(clazz), branches(std::move(branches)) {}

	shortInt classify(HeartDiseaseData::Set& sample);

	void print(std::ostream& os, size_t level);

private:
	size_t attribute;
	shortInt clazz;
	std::unordered_map<shortInt, std::unique_ptr<Node>> branches;
};

class ID3
{
public:
	shortInt classify(HeartDiseaseData::Set& sample);
	void print(std::ostream& os);
	/// root node of the decision tree.
	std::unique_ptr<Node> root;

	friend class ID3train;

	ID3(std::unique_ptr<Node>&& root)
		: root(std::move(root)){}

private:
	

};

class ID3Train
{
private:
	// some aliases.
	using sample = typename HeartDiseaseData::Set&;
	using iter = typename std::vector<sample&>::iterator;

public:
	ID3Train(std::vector<sample>&& samples)
		: samples(std::move(samples)){}

	std::unique_ptr<ID3> train();

private:
	std::unique_ptr<Node> trainit(iter start, iter end);
	std::vector<sample> samples;
};