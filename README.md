# Knoth engine

Este es un engine desarrollado de forma personal para el análisis de arquitectura y organización de un game engine. Se busca que la parte del engine se mantenga separada en un DLL para marcar de forma clara la separación entre lo que es juego y lo que es engine.

> [!WARNING]
> Todo está hecho para funcionar en Windows

Múltiples sistemas ya iniciaron su desarrollo, pero se quiere que tenga los siguientes elementos:
- [ ] Renderer
- [x] Layers
- [x] Logger
- [ ] Game objects (Components)
- [ ] Scripting
- [ ] Audio
- [ ] Localización
- [ ] Escenas/Mapas

## Descripción del engine
Para que la inicialización y control de elementos venga del lado del engine, tenemos un entry point en "Engine/Entrypoint.h", este implementa la función main, que se "insertará" en el proyecto del juego a través del KnothEngine.h. Esto nos permite quitarle decisiones de inicialización al usuario.

Lo que el usuario podrá implementar será un child de la clase "Application", la cual se encarga de filtrar los layers, los inputs y mantener el loop de update. Lo que se puede overridear está limitado actualmente a crear su propio constructor, pero se extenderá eventualmente para permitir otras implementaciones personalizadas.

Nuestros archivos de "apoyo" son:
- "Core.h", que funge como nuestra librería de definiciones, ya que se implementan macros para bindear eventos en std, dllexport/dllimport, Asserts y operaciones de bits
- "KnothEngine.h", que funge como la ubicación de todos los includes imprescindibles para el cliente, para evitar la necesidad de buscar mucho los includes que se requieren añadir
- "knothpch.h", para precompilar librerías de terceros

Actualmente el flujo de Update se encuentra de la siguiente forma:
1. Layer Update
2. ImGuiUpdate
3. Window Update

Los inputs y sus tiempos de manejo se explicarán en su sección, y la parte de renderizado, hasta este momento, todavía no está completada, por lo que no se incluye en esta secuencia.

### Window

Esta clase se encarga de encapsular y separar las diversas implementaciones específicas para cada plataforma, por lo que actualmente nada más implementa un struct general para el nombre de la ventana, ancho y alto. La clase en sí implementa las siguientes funciones sobreescribibles:
- Constructor
- OnUpdate()
- unsigned int GetWidth()
- unsigned int GetHeight()
- SetEventCallback(const EventCallbackFn&)
- SetVSync(bool)
- bool IsVSync()
- virtual void* GetNativeWindow()

Y finalmente está definida la función estática "Create", la cual se puede implementar en el cpp donde se implementa la versión específica de cada plataforma. Actualmente solo está implementada la versión de windows en "Platform/Windows/WindowsWindow", la cual utiliza glad para su funcionamiento.

### Layers

Los layers será la forma escencial en la que manejaremos "espacios" dentro del engine. Múltiples layers pueden ser añadidos al mismo tiempo, y estos serán manejados por el Layer Stack.
Un layer de forma base implementa las siguientes funciones:
- OnAttach(): Se llama cuando se agrega el layer al stack
- OnDetach(): Se llama cuando un layer se saca del stack
- OnUpdate()
- OnImGuiRender(): Se llama en caso de que este layer necesite dibujar algo con ImGuiRender
- OnEvent(Event&): Manejo de eventos específicos del layer, los puede consumir para que no pasen a layers inferiores

Los layers se añaden al stack añadiéndolos a través del Application, el cuál cuenta con las funciones:
- PushOverlay(Layer*): Agrega un layer que irá por encima de todas las anteriormente añadidas
- PushLayer(Layer*): Agrega un layer que irá por encima de otros layers, pero por debajo de los overlays

El encargado de mantener este orden es el "LayerStack", el cuál cuenta con las funciones de añadir y quitar Layers y Overlays, además de accesos a los iteradores de su lista, para poder iterar el array.

### Logger

> [!NOTE]
> Actualmente el logger únicamente imprime a consola, pero se planea que más adelante se guarden los registros.

El logger se inicializa en el entry point y antes del resto del engine (actualmente), debido a que todos los sistemas lo usan para imprimir en caso de error o mal funcionamiento de los sistemas.

Lo más importante del logger es que tiene la posibilidad de ser usado en su versión estática, a través del "Knoth::Log::GetLogger()", o a través de una instancia local. El acceso al logger está diseñado para que sea a través de macros, siendo los siguientes:
- Globales:
  - KNOTH_LOG(...)
  - KNOTH_INFO(...)
  - KNOTH_ERROR(...)
- Locales:
  - PRINT_LOG(...)
  - PRINT_INFO(...)
  - PRINT_ERROR(...)
 
Todos los prints utilizan la función de ["std::format"](https://en.cppreference.com/w/cpp/utility/format/format), por que llamar a cualquiera de las macros debe ser tratado como si se usara dicha función

> [!WARNING]
> No hay ninguna implementación del logger que soporte textos fuera del UNICODE

### Eventos de input

El sistema de inputs actualmente está integrado para que sean manejados en cualquier momento de la ejecución, ya que reciben el evento desde GLFW y lo mandan a todo el engine, y se maneja de en ese momento, esto se planea modificar más adelante para que, de forma interna en el juego, los inputs no sean manejados hasta un nuevo frame.

En Windows, como se mencionó anteriormente, el engine se apoya de GLFW para recibir los inputs, estos bindeos se hacen en el Init de WindowsWindow, donde podemos ver los bindeos usando lambdas y las clases de eventos, las cuales se encuentran declaradas en la carpeta de "Engine/Event". En su mayoría los tipos de eventos ya están implementados, pero las funciones a las que se tiene acceso son las siguientes:
- EventType GetEventType()
- const char* GetName()
- int GetCategoryFlags()
- std::string ToString()
- bool IsInCategory(EventCategory)
- bool IsHandled()
- bool Dispatch<T>(EventFn<T>)

La forma de manejar el evento, es a través de la función template "Dispatch", donde se indica el tipo de evento que se espera, y como parámetro se pasa un bindeo a una función que pide como input T& y retorna bool, ya de forma interna se compara, llama a la funcion, y cambia el valor de _Handled.

Para facilitar la lectura a lo largo de todo el engine, declaramos nuestros propios macros con definiciones específicas de los inputs, de base se usan los números implementados por GLFW, y en caso de ser necesario, se deberán implementar adaptaciones para otros sistemas, estas definiciones se encuentran en "Engine/Input".

## Librerías de terceros
- ImGui
- GLFW
- Glad
