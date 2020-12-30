#pragma once
#include<array>
#include<vector>
typedef long long LL;
const LL MaxSize=1000;
class SegmentTree
{
	struct node
	{
		LL start;
		LL end;
		LL sum;
		LL lazyFlag;
		bool isLeaf() { return start == end; }
		LL length() { return end - start + 1; }
	};
	enum class RelationShip
	{
		segIn,segOut,segCross
	};
	std::array<node, 2 * MaxSize+10> segmentArray;
	inline LL leftChild(LL position) { return  position<<1; }
	inline LL rightChild(LL position) { return  position<<1|1; }
	inline void buildHelper(LL position,LL start, LL end, const std::vector<LL>& data);
	inline RelationShip segRelation(node n, LL start, LL end)
	{
		if (end<n.start || start>n.end) return RelationShip::segOut;
		if (start<=n.start && end>=n.end) return RelationShip::segIn;
		return RelationShip::segCross;
	}
	void addHelper(LL position, LL start,LL end, LL value);
	void pushDown(LL position);
	void updateFlag(LL position, LL value){
		segmentArray[position].sum += value * segmentArray[position].length();
		segmentArray[position].lazyFlag += value;
	}
	void updateValue(LL position) {
		segmentArray[position].sum = segmentArray[leftChild(position)].sum + segmentArray[rightChild(position)].sum;
	};
	LL queryHelper(LL position, LL start, LL end);
public: 
	SegmentTree(const std::vector<LL>& data);
	void add(LL start, LL end, LL value);
	LL query(LL start, LL end);
};
inline void SegmentTree::addHelper(LL position, LL start,LL end, LL value)
{
	if (segRelation( segmentArray[position],start,end)==RelationShip::segIn)
	{
		updateFlag(position, value);
		return;
	} 
	pushDown(position);
	if (segRelation(segmentArray[leftChild(position)], start, end) != RelationShip::segOut)
	{
		addHelper(leftChild(position), start, end, value);
	}
	if (segRelation(segmentArray[rightChild(position)], start, end) != RelationShip::segOut)
	{
		addHelper(rightChild(position), start, end, value);
	}
	updateValue(position);
}
inline void SegmentTree::pushDown(LL position)
{
	LL lastLasyFlag = segmentArray[position].lazyFlag;
	segmentArray[position].lazyFlag = 0;
	updateFlag(leftChild(position), lastLasyFlag);
	updateFlag(rightChild(position), lastLasyFlag);
}
inline LL SegmentTree::queryHelper(LL position, LL start, LL end)
{
	if (segRelation(segmentArray[position], start, end) == RelationShip::segIn)
	{
		return segmentArray[position].sum;
	}
	if (segRelation(segmentArray[position], start, end) == RelationShip::segOut)
	{
		exit(4);
	}
	pushDown(position);
	LL s = 0;
	if (segRelation(segmentArray[leftChild(position)], start, end) != RelationShip::segOut)
	{
		s+=queryHelper(leftChild(position), start, end);
	}
	if (segRelation(segmentArray[rightChild(position)], start, end) != RelationShip::segOut)
	{
		s+=queryHelper(rightChild(position), start, end);
	}
	return s;
}
SegmentTree::SegmentTree(const std::vector<LL>& data)
{
	buildHelper(1, 1, data.size() - 1,data);
}
inline void SegmentTree::add(LL start, LL end, LL value)
{
	addHelper(1, start, end, value);
}
inline LL SegmentTree::query(LL start, LL end)
{
	return queryHelper(1, start, end);
}
inline void SegmentTree::buildHelper(LL position, LL start, LL end, const std::vector<LL>& data)
{
	if (start==end)
	{
		segmentArray[position] = { start,end,data[start],0 };
		return;
	}
	segmentArray[position].start = start;
	segmentArray[position].end = end;
	segmentArray[position].lazyFlag = 0;
	LL mid = (start + end) >> 1;
	buildHelper(leftChild(position), start, mid,data);
	buildHelper(rightChild(position), mid + 1, end, data);
	segmentArray[position].sum = segmentArray[leftChild(position)].sum + segmentArray[rightChild(position)].sum;

}