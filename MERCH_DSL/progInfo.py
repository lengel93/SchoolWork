class progInfo:
    '''
    Class Name:
        class progInfo

    Description:
        @TODO

    Todos/Known Bugs:
        None Known
    '''

    def __init__(self):
        '''
        Function Name:
            def __init__(self)

        Description:
            Constructor for the class, initializes two maps to hold the
            variables, and the tags for the gotos
        '''
        self.variables = {} #creates a map (dictionary)
        self.gotos = {}


    def addGoto(self, name, goto):
        '''
        Function Name:
            def addGoto(self, name, goto)

        Description:
            Adds a goto tag to the goto map. Before adding will remove the
            spaces from the name of the tag. The key is the name of the goto,
            it's contents is the gotos location.

        Arguments:
            name - the name of the tag
            goto - the location the goto goes to
        '''
        name = name.replace(" ", "")
        self.gotos[name] = goto

    def addVar(self, var, arr):
        '''
        Function Name:
            def addVar(self, var, arr)

        Description:
            Adds a variable to the variable map. Before adding will remove the
            spaces from the name of the variable. The key is the name of the
            variable, it's contents are the stocks it holds.

        Arguments:
            var - the name of the variables
            arr - the contents of the variable
        '''
        var = var.replace(" ", "")
        self.variables[var] = arr


    def getGoto(self, name):
        '''
        Function Name:
            def getGoto(self, name)

        Description:
            Returns the location of a goto in the map. If it does not exist, it
            returns infinity.

        Arguments:
            name - the name of the goto to find

        Returns:
            goto location
        '''
        try:
            return self.gotos[name]
        except:
            return float("inf")


    def getInclusion(self, var):
        '''
        Function Name:
            def getInclusion(self, var)

        Description:Checks the gotos map to see if a tag has been defined yet

        Arguments:
            var - the name of the tag we are checking was defined

        Returns:
            True - if tag has been defined
	    False - otherwise
        '''
        return var in self.gotos


    def getVar(self, var):
        '''
        Function Name:
            def getVar(self, var)

        Description:
            Returns the contents of a variable in the map. If it does not exist,
            it returns infinity.

        Arguments:
            var - the name of the variable to find

        Returns:
            contents of the variable
        '''
        try:
            return self.variables[var.replace(" ", "")]
        except:
            return float("inf")
