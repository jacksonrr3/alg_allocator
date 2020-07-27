# alg_allocator

Разработка менеджеров управления памяти , реализующих интерфейс std::allocator

1. allocator_interface.h   
  содержит класс Allocator_Interface, реализующий интерфейс std::allocator и позволяющий применять разные алгоримы выделения и распределения памяти. 
  Алгоритм работы с памятию задается шаблонным параметром. 
  Требования к классам, реализующим конкретные алгоритмы -  должен поддерживать реализацию методов allocate и deallocate.
  
2. Алгоритмы: 
linear_alg  - линейно выделяет память 
block_alg   - выделчяет блоки памяти по N элементов и предоставляет эту память по запросу. Освобождение памяти происходит одновременно.
stack_alg.h - пследовательно выделяет участки памяти, освобождает в обратном порядке.
first_fit   - распределяет память с ограниченного участка. при запросе на выделение памяти возвращает указатель на запрошенный участок памяти, или нулевой указатель.
при освобождении памяти соседние свободные участки объединяются в один.
List_alg    - разбивает выделенный участок памяти на блоки одинакового размера. свободные участки храняться в виде списка. 

