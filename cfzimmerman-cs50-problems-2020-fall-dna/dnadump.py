    
    
    for name in people:
        person_list = people[name]
        person_list.sort()
        result_list.sort()
        
        #del person_list[0]
        #del result_list[0]
        
        print(f"{name}")
        print(f"{person_list}")
        print(f"{result_list}\n")
        #print(f"{person_list[0]}")
        #print(f"{result_list[0]}\n")
        
        if (len(people) > 3):
            
            if (person_list == result_list):
                print(f"{name}")
                return
        elif (len(people) == 3):
            if ((person_list[-3] == result_list[-3]) and (person_list[-2] == result_list[-2]) and (person_list[-1] == result_list[-1])):
                print(f"{name}")
                return
            
    print("No match")