#ifndef __REFUND_H_INCLUDED__
#define __REFUND_H_INCLUDED__
#include <string>
using namespace std;
class refundClass{
public:
  string sellerName, buyerName;
  double credit;
  refundClass();
  bool refund();
};
//string refund();
#endif
