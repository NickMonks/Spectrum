#pragma once

#include "Spectrum/Core.h"

#include "Layer.h"

namespace Spectrum {
	class SP_API LayerStack
	{
		//Wrapper over the vector of layers, to storing the layers contiguously.
		// We store raw pointers of the layers 
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;


	};
}