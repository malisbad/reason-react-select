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
  let make = (_children) => {
    ...component,
    render: (_self) =>
      <input className="c-reason-select__input" />
  };
};

type actions =
  | Selected(SelectOption.t);
  
type state = {
  options: Options.t,
  selectedOption: SelectOption.t,
};

let defaultOption: SelectOption.t = {
  value: "",
  displayText: "",
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
  {
    ...component,
    initialState: () => {
      options: optionsList,
      selectedOption: defaultOption,
    },
    reducer: (action, state) =>
      switch action {
      | Selected(selectedOption) => ReasonReact.Update({ ...state, selectedOption })
    },
    render: (self) =>
      <div className="c-reason-select">
        <SelectDisplay displayText={self.state.selectedOption.displayText} />
        <SelectInput />
        <Options
          optionList={self.state.options}
          onSelect={self.handle(onSelectOption)}
        />
      </div>
  }
};
