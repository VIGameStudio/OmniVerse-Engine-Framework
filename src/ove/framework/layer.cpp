#include "layer.hpp"

using namespace ove::core;
using namespace ove::framework;

layer_mgr_t::layer_mgr_t(event_bus_t* pEventBus)
	: m_pEventBus(pEventBus)
{
}

layer_mgr_t::~layer_mgr_t()
{
}

void layer_mgr_t::addLayer(layer_base_t* pLayer)
{

}

void layer_mgr_t::removeLayer(layer_base_t* pLayer)
{

}