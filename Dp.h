#ifndef DP_H
#define DP_H

#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <iostream>

using namespace std;


class Grid {
public:
	Grid(int sz) {
		size = sz;
		for (int i = 0; i < sz; i = i + 1) {
			vector<float> temp;
			for (int a = 0; a < sz; a = a + 1) {
				temp.push_back(0.0);
			}
			G.push_back(temp);
		}
	}
	void operator= (Grid cpy) { this->G = cpy.G; }
	void show() {
		for (int a = 0; a < size; a = a + 1) {
			for (int b = 0; b < size; b = b + 1) {
				cout << G[a][b] << "  |  ";
			}
			cout << endl;
		}
	}

	vector<vector<float>> G;
	int size = 4;
};



class DP
{
public:
	enum Action { up, right, left, down };
	DP() {};
	~DP() {};

	void ValueIter(float threshold) {
		// This is a non-discount procedure (discount = 1)
		while (true)
		{
			Grid NewGd = Grid(GridSize);
			float Delta = 0;
			for (int p = 0; p < GridSize; p = p + 1) {
				for (int q = 0; q < GridSize; q = q + 1) {
					if (T(p, q)) { continue; }
					for (map<Action, float>::iterator iter = Prob.begin(); iter != Prob.end(); iter++) {
						int a = p; int b = q;
						Nxt(a, b, iter->first);
						NewGd.G[p][q] = NewGd.G[p][q] + (iter->second)*(reward + Gd.G[a][b]);
					}
					Delta = (abs(NewGd.G[p][q] - Gd.G[p][q]) > Delta) ? abs(NewGd.G[p][q] - Gd.G[p][q]) : Delta;
				}
			}
			Gd = NewGd;
			if (Delta < threshold) { break; }
		}
	}
	void Policy() {
		P.resize(GridSize);
		for (int a = 0; a < GridSize; a = a + 1) {
			P[a].resize(GridSize);
		}
		for (int p = 0; p < GridSize; p++)
		{
			for (int q = 0; q < GridSize; q++)
			{
				if (T(p, q)) { P[p][q] = "Ter"; continue; }
				vector<float> v = {};
				for (map<Action, string>::iterator iter = Symbol.begin(); iter != Symbol.end(); iter++) {
					int a = p; int b = q;
					if (Nxt(a, b, iter->first)) {Comp(v, Gd.G[a][b], P[p][q], iter->second);}
				}
			}
		}
	}
	void show() { Gd.show(); }
	void showpolicy() {
		for (int a = 0; a < GridSize; a = a + 1) {
			for (int b = 0; b < GridSize; b = b + 1) {
				cout << P[a][b] << "  |  ";
			}
			cout << '\n';
		}
	}
protected:
	// Assume that if the next state out of boundary, return to the current state
	bool Nxt(int& x, int& y, const Action& act) {
		if (act == up) {
			if (B(x - 1, y)) { x = x - 1; return true; }
			else { return false; }
		}
		else if (act == down) {
			if (B(x + 1, y)) { x = x + 1; return true; }
			else { return false; }
		}
		else if (act == left) {
			if (B(x, y - 1)) { y = y - 1; return true; }
			else { return false; }
		}
		else if (act == right) {
			if (B(x, y + 1)) { y = y + 1; return true; }
			else { return false; }
		}
		return true;
	}

	// It defines the border and the block area
	// If it is a block --> false
	bool B(const int& x, const int& y) {
		if (x<0 || x>GridSize - 1) { return false; }
		if (y<0 || y>GridSize - 1) { return false; }
		for (vector<vector<int>>::iterator iter = Block.begin(); iter != Block.end(); iter++) {
			if (*iter == vector<int>{x, y}) {
				return false;
			}
		}
		return true;
	}

	// If it is a terminal -->true
	bool T(const int& x, const int& y) {
		for (vector<vector<int>>::iterator iter = Terminal.begin(); iter != Terminal.end(); iter++) {
			if (*iter == vector<int>{x, y}) {
				return true;
			}
		}
	}

	void Comp(vector<float>& v, float value, string& st, const string& output) {
		if (v.empty()) { st = output; v.push_back(value); return; }
		else {
			if (value > v[0]) {
				st = output; v[0] = value; return;
			}
			else if (value == v[0]) {
				st = st + " , "+ output; return;
			}
			return;
		}
	}
private:
	Grid Gd = Grid(5);
	int GridSize = 5;
	vector<vector<string>> P = { {} };
	vector<vector<int>> Terminal = { {0,0},{4,4} };
	vector<vector<int>> Block = { {} };

	// The policy is to follow any direction Randomly (equal probability)
	map<Action, float> Prob =
	{ {up, 0.25}, {down, 0.25}, {left,0.25},{right,0.25} };

	map<Action, string> Symbol =
	{
		{up, "up"}, {down, "down"},
		{left, "left"}, {right, "right"}
	};

	// the reward is always -1 for each action
	float reward = -1.0;
};

#endif // !DP_H
#pragma once
