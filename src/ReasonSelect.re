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
            className="o-reason-select__option"
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
  let make = (~optionList: t, ~isHidden, ~onSelect, _children) => {
    ...component,
    render: (_self) => 
    <div className="o-reason-select__option-list" hidden={isHidden} >
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
  let defaultStyle = ReactDOMRe.Style.make(~alignItems="center", ~border="1px solid #a6a6a6", ~display="flex", ~height="50px", ~padding="5px 15px", ~width="100%", ());

  let component = ReasonReact.statelessComponent("SelectDisplay");
  let make = (~displayText="", ~onClick, _children) => {
    ...component,
    render: (_self) =>
      <div className="o-reason-select__display" style={defaultStyle} onClick>
        {ReasonReact.string(displayText)}
      </div>
  };
};

module SelectInput = {
  let defaultStyle = ReactDOMRe.Style.make(~alignItems="center", ~border="1px solid #a6a6a6", ~height="50px", ~padding="5px 15px", ~width="100%", ());

  let component = ReasonReact.statelessComponent("SelectInput");
  let make = (~isHidden, ~handleChange, _children) => {
    ...component,
    render: (_self) =>
      <input
        className="o-reason-select__input"
        onChange={ev => handleChange(ReactEvent.Form.target(ev)##value)}
        style={defaultStyle}
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
      <div className="o-reason-select">
        <SelectDisplay
          displayText={self.state.selectedOption.displayText}
          onClick={self.handle(onDisplayClick)}
        />
        <SelectInput
          handleChange={self.handle(onFilterChange)}
          isHidden={self.state.isHidden}
        />
        <Options
          optionList={self.state.filteredList}
          onSelect={self.handle(onSelectOption)}
          isHidden={self.state.isHidden}
        />
      </div>
  }
};
