#include <iostream>
#include <list>
#include <ostream>
#include "vertex.h"
#include "edge.h"
#include "grafo.h"
using namespace std;

int main()
{
    // Grafo<int, int> MALLA;

    // MALLA.Insert_Vertex(0);
    // MALLA.Insert_Vertex(1);
    // MALLA.Insert_Vertex(2);
    // MALLA.Insert_Vertex(3);
    // MALLA.Insert_Vertex(4);
    // MALLA.Insert_Vertex(5);

    // MALLA.Insert_Arista(5,0,0);
    // MALLA.Insert_Arista(5,2,0);
    // MALLA.Insert_Arista(4,0,0);
    // MALLA.Insert_Arista(4,1,0);
    // MALLA.Insert_Arista(2,3,0);
    // MALLA.Insert_Arista(3,1,0);

    // MALLA.graficar("prueba.dot");
    // MALLA.graficar("prueba.dot");
    // system("dot prueba.dot -o prueba.png -Tpng");           //dot grafo.dot -o grafo.png -Tpng
    // system("prueba.png");

    // MALLA.verAdyacencias();
    // MALLA.topologicalSort();
    

    Grafo<string, int> MALLA;
    // 1er año: semestre 1
    MALLA.Insert_Vertex("Fundamentos_de_Computacion");
    MALLA.Insert_Vertex("Ingles_Tecnico_Profesional_1");
    MALLA.Insert_Vertex("Estructuras_Discretas_1");
    MALLA.Insert_Vertex("Razonamiento_Logico_Matematico");
    MALLA.Insert_Vertex("Metodologia_del_Trabajo_Intelectual_Universitario");
    MALLA.Insert_Vertex("Arte_Computacional");
    MALLA.Insert_Vertex("Liderazgo_y_Oratoria");
    // 1er año: semestre 2
    MALLA.Insert_Vertex("Estructuras_Discretas_2");
    MALLA.Insert_Vertex("Ciencia_de_la_Computacion_1");
    MALLA.Insert_Vertex("Calculo_en_una_Variable");
    MALLA.Insert_Vertex("Ingles_Tecnico_Profesional_2");
    MALLA.Insert_Vertex("Comunicacion_Integral");
    MALLA.Insert_Vertex("Realidad_Nacional");
    // 2do: semestre 1
    MALLA.Insert_Vertex("Arquitectura_de_Computadores");
    MALLA.Insert_Vertex("Ciencia_de_la_Computacion_2");
    MALLA.Insert_Vertex("Trabajo_Interdisciplinar_1");
    MALLA.Insert_Vertex("Calculo_en_Varias_Variables");
    MALLA.Insert_Vertex("Ingles_Tecnico_Profesional_3");
    MALLA.Insert_Vertex("Desarrollo_Basado_en_Plataformas");
    MALLA.Insert_Vertex("Ciudadania_e_Interculturalidad");
    // 2do: semestre 2
    MALLA.Insert_Vertex("Algoritmos_y_Estructuras_de_Datos");
    MALLA.Insert_Vertex("Teoria_de_la_Computacion");
    MALLA.Insert_Vertex("Base_de_Datos_1");
    MALLA.Insert_Vertex("Algebra_Lineal_Numerica");
    MALLA.Insert_Vertex("Estadistica_y_Probabilidades");
    MALLA.Insert_Vertex("Ecologia_y_Conservacion_Ambiental");
    // 3er: semestre 1
    MALLA.Insert_Vertex("Base_de_Datos_2");
    MALLA.Insert_Vertex("Analisis_y_Diseño_de_Algoritmos");
    MALLA.Insert_Vertex("Ingenieria_de_Software_1");
    MALLA.Insert_Vertex("Analisis_Exploratorio_de_Datos_Espaciales");
    MALLA.Insert_Vertex("Ecuaciones_Diferenciales");
    MALLA.Insert_Vertex("Compiladores");
    // 3er: semestre 2
    MALLA.Insert_Vertex("Programacion_Competitiva");
    MALLA.Insert_Vertex("Ingenieria_de_Software_2");
    MALLA.Insert_Vertex("Estructuras_de_Datos_Avanzados");
    MALLA.Insert_Vertex("Sistemas_Operativos");
    MALLA.Insert_Vertex("Trabajo_Interdisciplinar_2");
    MALLA.Insert_Vertex("Matematicas_Aplicadas_a_la_Computacion");
    // 4to: semestre 1
    MALLA.Insert_Vertex("Investigacion_en_Ciencias_de_la_Computacion");
    MALLA.Insert_Vertex("Desarrollo_de_Software_Empresarial");
    MALLA.Insert_Vertex("Redes_y_Comunicacion");
    MALLA.Insert_Vertex("Ingenieria_de_Software_3");
    MALLA.Insert_Vertex("Computacion_Grafica");
    MALLA.Insert_Vertex("Inteligencia_Artificial");
    // 4to: semestre 2
    MALLA.Insert_Vertex("Proyecto_Final_de_Carrera_1");
    MALLA.Insert_Vertex("Computacion_Paralela_y_Distribuida");
    MALLA.Insert_Vertex("Seguridad_en_Computacion");
    MALLA.Insert_Vertex("Formacion_de_Empresas_de_Base_Tecnologica_1");
    MALLA.Insert_Vertex("Interaccion_Humano_Computador");
    MALLA.Insert_Vertex("Relaciones_Humanas");
    MALLA.Insert_Vertex("Fisica_Computacional");
    MALLA.Insert_Vertex("Topicos_en_Ingenieria_de_Software");
    // 5to: semestre 1
    MALLA.Insert_Vertex("Proyecto_Final_de_Carrera_2");
    MALLA.Insert_Vertex("Big_Data");
    MALLA.Insert_Vertex("Topicos_en_Inteligencia_Artificial");
    MALLA.Insert_Vertex("Etica_General_y_Profesional");
    MALLA.Insert_Vertex("Formacion_de_Empresas_de_Base_Tecnologica_2");
    MALLA.Insert_Vertex("Ingles_Tecnico_Profesional_4");
    MALLA.Insert_Vertex("Topicos_en_Ciencia_de_Datos");
    MALLA.Insert_Vertex("Topicos_en_Computacion_Grafica");
    MALLA.Insert_Vertex("Bioinformatica");
    // 5to: semestre 1
    MALLA.Insert_Vertex("Cloud_Computing");
    MALLA.Insert_Vertex("Proyecto_Final_de_Carrera_3");
    MALLA.Insert_Vertex("Trabajo_Interdisciplinar_3");
    MALLA.Insert_Vertex("Internet_de_las_Cosas");
    MALLA.Insert_Vertex("Robotica");
    MALLA.Insert_Vertex("Topicos_en_Ciberseguridad");

    // ARISTAS
    //1er año 
    //1er semestre 
    MALLA.Insert_Arista("Fundamentos_de_Computacion" , "Estructuras_Discretas_2", 1);
    MALLA.Insert_Arista("Fundamentos_de_Computacion" , "Ciencia_de_la_Computacion_1", 1);
    MALLA.Insert_Arista("Ingles_Tecnico_Profesional_1" , "Ingles_Tecnico_Profesional_2", 1);
    MALLA.Insert_Arista("Estructuras_Discretas_1" , "Estructuras_Discretas_2", 1);
    //2do semestres
    MALLA.Insert_Arista("Estructuras_Discretas_2" , "Arquitectura_de_Computadores", 1);
    MALLA.Insert_Arista("Estructuras_Discretas_2" , "Teoria_de_la_Computacion", 1);
    MALLA.Insert_Arista("Estructuras_Discretas_2" , "Base_de_Datos_1", 1);
    MALLA.Insert_Arista("Ciencia_de_la_Computacion_1" , "Ciencia_de_la_Computacion_2", 1);
    MALLA.Insert_Arista("Ciencia_de_la_Computacion_1" , "Desarrollo_Basado_en_Plataformas", 1);
    MALLA.Insert_Arista("Ciencia_de_la_Computacion_1" , "Trabajo_Interdisciplinar_1", 1);
    MALLA.Insert_Arista("Ciencia_de_la_Computacion_1" , "Base_de_Datos_1", 1);
    MALLA.Insert_Arista("Calculo_en_una_Variable" , "Calculo_en_Varias_Variables", 1);
    MALLA.Insert_Arista("Ingles_Tecnico_Profesional_2" , "Ingles_Tecnico_Profesional_3", 1);

    // 2do año
    // 1er semestre 
    MALLA.Insert_Arista("Arquitectura_de_Computadores" , "Sistemas_Operativos", 1);
    MALLA.Insert_Arista("Ciencia_de_la_Computacion_2" , "Algoritmos_y_Estructuras_de_Datos", 1);
    MALLA.Insert_Arista("Ciencia_de_la_Computacion_2" , "Ingenieria_de_Software_1", 1);
    MALLA.Insert_Arista("Trabajo_Interdisciplinar_1" , "Trabajo_Interdisciplinar_2", 1);
    MALLA.Insert_Arista("Calculo_en_Varias_Variables", "Estadistica_y_Probabilidades", 1);
    MALLA.Insert_Arista("Calculo_en_Varias_Variables" , "Ecuaciones_Diferenciales", 1);
    MALLA.Insert_Arista("Ingles_Tecnico_Profesional_3" , "Ingles_Tecnico_Profesional_4", 1);
    // 2do semestre
    MALLA.Insert_Arista("Algoritmos_y_Estructuras_de_Datos" , "Analisis_y_Diseño_de_Algoritmos", 1);
    MALLA.Insert_Arista("Algoritmos_y_Estructuras_de_Datos" , "Analisis_Exploratorio_de_Datos_Espaciales", 1);
    MALLA.Insert_Arista("Teoria_de_la_Computacion" , "Compiladores", 1);
    MALLA.Insert_Arista("Base_de_Datos_1" , "Base_de_Datos_2", 1);
    MALLA.Insert_Arista("Base_de_Datos_1" , "Ingenieria_de_Software_1", 1);
    MALLA.Insert_Arista("Algebra_Lineal_Numerica" , "Ecuaciones_Diferenciales", 1);
    MALLA.Insert_Arista("Estadistica_y_Probabilidades" , "Analisis_Exploratorio_de_Datos_Espaciales", 1);
    MALLA.Insert_Arista("Estadistica_y_Probabilidades" , "Inteligencia_Artificial", 1);

    //3er año
    // 1er semestre
    MALLA.Insert_Arista("Base_de_Datos_2" , "Big_Data", 1);
    MALLA.Insert_Arista("Analisis_y_Diseño_de_Algoritmos" , "Programacion_Competitiva", 1);
    MALLA.Insert_Arista("Analisis_y_Diseño_de_Algoritmos" , "Estructuras_de_Datos_Avanzados", 1);
    MALLA.Insert_Arista("Analisis_y_Diseño_de_Algoritmos" , "Investigacion_en_Ciencias_de_la_Computacion", 1);
    MALLA.Insert_Arista("Ingenieria_de_Software_1" , "Ingenieria_de_Software_2", 1);
    MALLA.Insert_Arista("Ingenieria_de_Software_1" , "Desarrollo_de_Software_Empresarial", 1);
    MALLA.Insert_Arista("Analisis_Exploratorio_de_Datos_Espaciales" , "Topicos_en_Ciencia_de_Datos", 1);
    MALLA.Insert_Arista("Ecuaciones_Diferenciales" , "Matematicas_Aplicadas_a_la_Computacion", 1);

    // 2do semestre
    MALLA.Insert_Arista("Programacion_Competitiva" , "Computacion_Paralela_y_Distribuida", 1);
    MALLA.Insert_Arista("Ingenieria_de_Software_2" , "Ingenieria_de_Software_3", 1);
    MALLA.Insert_Arista("Estructuras_de_Datos_Avanzados" , "Computacion_Grafica", 1);
    MALLA.Insert_Arista("Sistemas_Operativos" , "Redes_y_Comunicacion", 1);
    MALLA.Insert_Arista("Trabajo_Interdisciplinar_2" , "Trabajo_Interdisciplinar_3", 1);
    MALLA.Insert_Arista("Matematicas_Aplicadas_a_la_Computacion" , "Fisica_Computacional", 1);

    // 4to año 
    // 1er semestre
    MALLA.Insert_Arista("Investigacion_en_Ciencias_de_la_Computacion" , "Proyecto_Final_de_Carrera_1", 1);
    MALLA.Insert_Arista("Investigacion_en_Ciencias_de_la_Computacion" , "Formacion_de_Empresas_de_Base_Tecnologica_1", 1);
    MALLA.Insert_Arista("Desarrollo_de_Software_Empresarial" , "Interaccion_Humano_Computador", 1);
    MALLA.Insert_Arista("Redes_y_Comunicacion" , "Seguridad_en_Computacion", 1);
    MALLA.Insert_Arista("Ingenieria_de_Software_3" , "Topicos_en_Ingenieria_de_Software", 1);
    MALLA.Insert_Arista("Computacion_Grafica" , "Topicos_en_Computacion_Grafica", 1);
    MALLA.Insert_Arista("Inteligencia_Artificial" , "Topicos_en_Inteligencia_Artificial", 1);
    // 2do semestre
    MALLA.Insert_Arista("Proyecto_Final_de_Carrera_1" , "Proyecto_Final_de_Carrera_2", 1);
    MALLA.Insert_Arista("Computacion_Paralela_y_Distribuida" , "Big_Data", 1);
    MALLA.Insert_Arista("Computacion_Paralela_y_Distribuida" , "Internet_de_las_Cosas", 1);
    MALLA.Insert_Arista("Seguridad_en_Computacion" , "Topicos_en_Ciberseguridad", 1);
    MALLA.Insert_Arista("Formacion_de_Empresas_de_Base_Tecnologica_1" , "Formacion_de_Empresas_de_Base_Tecnologica_2", 1);

    // 5to año 
    // 1er semestre
    MALLA.Insert_Arista("Proyecto_Final_de_Carrera_2" , "Proyecto_Final_de_Carrera_3", 1);
    MALLA.Insert_Arista("Big_Data" , "Cloud_Computing", 1);
    MALLA.Insert_Arista("Topicos_en_Inteligencia_Artificial" , "Robotica", 1);
    // 2do semestre

    MALLA.graficar("MALLA_CURRICULAR_UNSA.dot");
    MALLA.graficar("MALLA_CURRICULAR_UNSA.dot");
    system("dot MALLA_CURRICULAR_UNSA.dot -o MALLA_CURRICULAR_UNSA.png -Tpng");           //dot grafo.dot -o grafo.png -Tpng
    system("MALLA_CURRICULAR_UNSA.png");

    cout<<"\nMOSTRAND ORDEN TOPOLOGICO\n";
    MALLA.topologicalSort();
}