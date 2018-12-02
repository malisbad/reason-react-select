module SelectOption = {
  type t = {
    value: string,
    displayText: string,
  };

  let component = ReasonReact.statelessComponent("SelectOption");
  let make = (~option: t, ~handleClick, ~optionClassList, _children) => {
      ...component,
      render: (_self) => {
          <div
            className={"o-reason-select__option" ++ optionClassList}
            onClick={_ev => handleClick(option)}  
          >
            {ReasonReact.string(option.displayText)}
          </div>
      }
  };
};

module Options = {
  type t = array(SelectOption.t);

  let component = ReasonReact.statelessComponent("Options");
  let make = (~optionList: t, ~isHidden, ~onSelect, ~optionClassList, ~optionListClassList, _children) => {
    ...component,
    render: (_self) => 
    <div className={"o-reason-select__option-list" ++ optionListClassList} hidden={isHidden} >
      (
        ReasonReact.array(
          Belt.Array.map(optionList, option => {
            <SelectOption
              option
              optionClassList
              handleClick={onSelect} 
              key={option.value}
            />
          })
        )
      )
    </div>
  };
};

module SelectDisplay = {
  let component = ReasonReact.statelessComponent("SelectDisplay");
  let make = (~displayText="", ~onClick, ~selectClassList, _children) => {
    ...component,
    render: (_self) =>
      <div className={"o-reason-select__display" ++ selectClassList}
        onClick
      >
        {ReasonReact.string(displayText)}
      </div>
  };
};

module SelectInput = {
  let component = ReasonReact.statelessComponent("SelectInput");
  let make = (~isHidden, ~handleChange, ~inputClassList, _children) => {
    ...component,
    render: (_self) =>
      <input
        className={"o-reason-select__input" ++ inputClassList}
        onChange={ev => handleChange(ReactEvent.Form.target(ev)##value)}
        hidden={isHidden}
      />
  };
};

type actions =
  | ToggleList
  | Selected(SelectOption.t)
  | UpdateFilter(string)
  | UpdateFilteredList(Options.t)
  ;
  
type state = {
  isHidden: bool,
  options: Options.t,
  filteredList: Options.t,
  selectedOption: SelectOption.t,
  filter: string,
};

let defaultOption: SelectOption.t = {
  value: "",
  displayText: "",
};

let filterOptions = (filter, options) => {
  Belt.Array.keep(options: Options.t, option: bool => Js.String.includes(filter, option.displayText));
};

let component = ReasonReact.reducerComponent("Select");
let make = (
    ~onSelect={(value) => Js.log(value)},
    ~optionsList=[||],
    ~selectClassList="",
    ~inputClassList="",
    ~optionListClassList="",
    ~optionClassList="",
    _children
  ) => {
  let onSelectOption = (selectedOption, self) => {
    self.ReasonReact.send(Selected(selectedOption));
    onSelect(selectedOption.value);
  };
  let onFilterChange = (filter, self) => {
    self.ReasonReact.send(UpdateFilter(filter))
  };
  let onDisplayClick = (_, self) => {
    self.ReasonReact.send(ToggleList)
  };
  {
    ...component,
    initialState: () => {
      isHidden: true,
      options: optionsList,
      filteredList: optionsList,
      selectedOption: defaultOption,
      filter: "",
    },
    reducer: (action, state) =>
      switch action {
      | ToggleList => ReasonReact.Update({ ...state, isHidden: !state.isHidden })
      | Selected(selectedOption) => ReasonReact.Update({ ...state, selectedOption, isHidden: true })
      | UpdateFilter(filter) => ReasonReact.UpdateWithSideEffects(
          { ...state, filter },
          self => self.send(UpdateFilteredList(filterOptions(filter, self.state.options)))
        )
      | UpdateFilteredList(filteredList) => ReasonReact.Update({ ...state, filteredList })
    },
    render: (self) =>
      <div className={"o-reason-select" ++ selectClassList} >
        <SelectDisplay
          displayText={self.state.selectedOption.displayText}
          onClick={self.handle(onDisplayClick)}
          selectClassList
        />
        <SelectInput
          handleChange={self.handle(onFilterChange)}
          isHidden={self.state.isHidden}
          inputClassList
        />
        <Options
          optionList={self.state.filteredList}
          onSelect={self.handle(onSelectOption)}
          isHidden={self.state.isHidden}
          optionClassList
          optionListClassList
        />
      </div>
  }
};
