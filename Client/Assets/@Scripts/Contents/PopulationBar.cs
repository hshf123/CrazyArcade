using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PopulationBar : MonoBehaviour
{
    [SerializeField]
    Transform _populationBar;

    public void SetPopulationBar(float ratio)
    {
        ratio = Mathf.Clamp(ratio, 0, 1);
        _populationBar.localScale = new Vector3(ratio, 1, 1);
    }

    public void SetPopulationBar(int population, int maxPopulation)
    {
        float ratio = population / (float)maxPopulation;
        SetPopulationBar(ratio);
    }
}
