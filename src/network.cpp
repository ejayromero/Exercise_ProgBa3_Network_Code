#include "network.h"
#include "random.h"
#include <algorithm>
#include <iostream>

void Network::resize(const size_t& n)
{
	values.clear();
	values.resize(n);
	RandomNumbers r;
	r.normal(values);
}

bool Network::add_link(const size_t& a, const size_t& b)
{
	if ((a==b) or (a>size()-1) or (b>size()-1) or links.find(a)->second==b)
	{ 
		return false;
	} else {
		links.insert(std::pair <size_t, size_t> (a,b));
		links.insert(std::pair <size_t, size_t> (b,a));
		return true;
	}
}

size_t Network::random_connect(const double& mean_deg)
{
	size_t nb_links(0);
    links.clear();
    for(size_t i(0);i<values.size();++i)
    {
        RandomNumbers n;
        size_t degree (n.poisson(mean_deg));
        if(degree<0) degree=0;
        for(size_t j(0); j<degree ;++j)
        {
            if(add_link(i,n.uniform_double(0,values.size()-1))) ++nb_links;            
        }
    }
    return nb_links;
}

size_t Network::set_values(const std::vector<double>& new_values)
{
	size_t i(0);
	if (size()< new_values.size()) 
	{
		set_vector(new_values,i,size());
		return size();
	} else { 
		set_vector(new_values,i,new_values.size());
		return new_values.size();
	}
}

size_t Network::size() const
{
	return values.size();
}

size_t Network::degree(const size_t &_n) const
{
	return links.count(_n);
}

double Network::value(const size_t &_n) const
{
	return values[_n];
}

 std::vector<double> Network::sorted_values() const
 {
	std::vector<double> new_values(values);
	std::sort(new_values.begin(), new_values.end());
	std::reverse(new_values.begin(), new_values.end());
	return new_values;
 }

std::vector<size_t> Network::neighbors(const size_t& n) const
{
	auto iter(links.equal_range(n));
	std::vector<size_t> neighbor;
	for (auto it(iter.first); it!=iter.second; ++it)
      {
		  neighbor.push_back(it->second);
	  }
	return neighbor;
}

void Network::set_vector(const std::vector<double> new_vector,const size_t start,const size_t end)
{
	for (size_t i(start); i < end; ++i)
	{
		values[i]=new_vector[i];
	}
}
