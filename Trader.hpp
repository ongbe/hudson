/*
 * Trader.hpp
 */

#ifndef _TRADER_HPP_
#define _TRADER_HPP_

#ifdef WIN32
#pragma warning (disable:4290)
#endif

// STL
#include <string>

// Boost
#include <boost/date_time/gregorian/gregorian.hpp>

// Hudson
#include "PositionSet.hpp"

class Price;


class TraderException: public std::exception
{
public:
  TraderException(const std::string& what):
	_what(what)
  {
  }

  virtual ~TraderException(void) throw() { }
  virtual const char* what(void) throw() { return _what.c_str(); }

protected:
  std::string _what;
};


class Trader
{
public:
  Trader(void);

  // Buy/Sell
  Position::ID buy(const std::string& symbol, const boost::gregorian::date& dt, const Price& price, unsigned size = 1) throw(TraderException);  
  void buy(Position::ID, const boost::gregorian::date& dt, const Price& price, unsigned size = 1) throw(TraderException);
  void sell(Position::ID, const boost::gregorian::date& dt, const Price& price, unsigned size = 1) throw(TraderException);

  // Short Sell/Cover
  Position::ID sell_short(const std::string& symbol, const boost::gregorian::date& dt, const Price& price, unsigned size = 1) throw(TraderException);
  void sell_short(Position::ID, const boost::gregorian::date& dt, const Price& price, unsigned size = 1) throw(TraderException);
  void cover(Position::ID, const boost::gregorian::date& dt, const Price& price, unsigned size = 1) throw(TraderException);

  // Close
  void close(Position::ID, const boost::gregorian::date& dt, const Price& price) throw(TraderException);

  const PositionSet positions(void) const { return _miPositions; }

protected:
  Position::ID _pid;
  PositionSet _miPositions;
};

#endif // _TRADER_HPP_
