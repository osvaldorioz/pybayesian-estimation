from fastapi import FastAPI
import bayesian_estimation
import time
from pydantic import BaseModel
from typing import List
import json

app = FastAPI()

# Definir el modelo para la matriz
class Matrix(BaseModel):
    matrix: List[List[float]]

# Definir el modelo para el vector
class Vector(BaseModel):
    vector: List[float]

@app.post("/bayest")
async def cc(prior_mean: float,
             prior_variance: float,
             observation_variance: float,
             observations: Vector):
    start = time.time()
    
    # Inicializar con media a priori = 0, varianza a priori = 1, varianza de observación = 0.5
    estimator = bayesian_estimation.BayesianEstimator(prior_mean, 
                                                      prior_variance, 
                                                      observation_variance)

    #observations = [1.2, 0.8, 1.5, 1.1]  # Ejemplo de observaciones

    ii = 1
    str = ""
    for obs in observations.vector:
        estimator.update(obs)
        str += f"Posterior mean {ii}: {estimator.get_mean()}, Posterior variance {ii}: {estimator.get_variance()} | "
        ii += 1

    end = time.time()

    var1 = end - start

    j1 = {
        "Time taken in seconds": var1,
        "Resultados": str
    }
    jj = json.dumps(j1)

    return jj