
Este programa utiliza una distribución gaussiana como la distribución a priori y actualiza esta creencia en base a datos observados. El algoritmo supone que cada nueva observación viene de una distribución normal, 
y el objetivo es ajustar las creencias sobre la media de esta distribución.
Explicación del Código

    Clase BayesianEstimator:
        La clase toma como entrada un valor inicial para la media a priori, la varianza a priori y la varianza de observación (asumida constante para todas las observaciones).
        El método update calcula la media y varianza posterior utilizando una regla de combinación bayesiana. Cada observación nueva ajusta la creencia de la media en función de la observación y su varianza.

    Método update:
        Calcula la media posterior y la varianza posterior basándose en la media y varianza a priori, así como la observación actual.
        Ajusta los valores a los posteriores para reflejar la actualización en el estado de la clase.

    Enlace de Pybind11:
        El módulo expone la clase BayesianEstimator a Python, permitiendo la creación de instancias, actualizaciones y obtención de resultados de la estimación.
