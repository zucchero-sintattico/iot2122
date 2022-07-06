package com.mazzo.andru.testa.gardenapp.fragment

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.View
import com.mazzo.andru.testa.gardenapp.R
import com.mazzo.andru.testa.gardenapp.model.UIComponents

class IrrigationFragment : Fragment(R.layout.fragment_irrigation), UIComponents {

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        if(activity != null){
            this.bindAllComponents()
            this.setAllListeners()
        }
    }

    override fun onResume() {
        super.onResume()
    }

    override fun bindAllComponents() {

    }

    override fun setAllListeners() {

    }
}