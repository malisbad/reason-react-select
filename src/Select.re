module SelectOption = {
  type t = {
    value: string,
    displayText: string,
  };

  let component = ReasonReact.statelessComponent("SelectOption");
  let make = (~option: t, ~handleClick, _children) => {
      ...component,
      render: (_self) => {
          <div
            className="c-reason-select__option"
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
  let make = (~optionList: t, ~onSelect, _children) => {
    ...component,
    render: (_self) => 
    <div className="c-reason-select__option-list">
      (
        ReasonReact.array(
          Belt.Array.map(optionList, option => {
            <SelectOption
              option
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
  let make = (~displayText="", _children) => {
    ...component,
    render: (_self) =>
      <div className="c-reason-select__display-wrapper">
        {ReasonReact.string(displayText)}
      </div>
  };
};

module SelectInput = {
  let component = ReasonReact.statelessComponent("SelectInput");
  let make = (~handleChange, _children) => {
    ...component,
    render: (_self) =>
      <input
        className="c-reason-select__input"
        onChange={ev => handleChange(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(ev))##value)}
      />
  };
};

type actions =
  | Selected(SelectOption.t)
  | UpdateFilter(string)
  | UpdateFilteredList(Options.t)
  ;
  
type state = {
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
  Js.log(filter);
  Belt.Array.keep(options: Options.t, option: bool => Js.String.includes(filter, option.displayText));
};

let component = ReasonReact.reducerComponent("Select");
let make = (
    ~onSelect={(value) => Js.log(value)},
    ~optionsList=[||],
    _children
  ) => {
  let onSelectOption = (selectedOption, self) => {
    self.ReasonReact.send(Selected(selectedOption));
    onSelect(selectedOption.value);
  };
  let onFilterChange = (filter, self) => {
    self.ReasonReact.send(UpdateFilter(filter))
  };
  {
    ...component,
    initialState: () => {
      options: optionsList,
      filteredList: optionsList,
      selectedOption: defaultOption,
      filter: "",
    },
    reducer: (action, state) =>
      switch action {
      | Selected(selectedOption) => ReasonReact.Update({ ...state, selectedOption })
      | UpdateFilter(filter) => ReasonReact.UpdateWithSideEffects(
          { ...state, filter },
          self => self.send(UpdateFilteredList(filterOptions(filter, self.state.options)))
        )
      | UpdateFilteredList(filteredList) => ReasonReact.Update({ ...state, filteredList })
    },
    render: (self) =>
      <div className="c-reason-select">
        <SelectDisplay displayText={self.state.selectedOption.displayText} />
        <SelectInput handleChange={self.handle(onFilterChange)} />
        <Options
          optionList={self.state.filteredList}
          onSelect={self.handle(onSelectOption)}
        />
      </div>
  }
};
